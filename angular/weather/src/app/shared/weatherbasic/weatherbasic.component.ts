import { Component, ElementRef, ViewChild, OnInit, OnDestroy, inject, signal } from '@angular/core';
import lottie, { AnimationItem } from 'lottie-web';
import { WeatherReaderService } from '../../services/services/weather-reader.service';
import { WeatherBasic } from '../../models/weather-basic.model';
import { Subject, timer, switchMap, takeUntil, tap } from 'rxjs';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatCardModule } from '@angular/material/card';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-weatherbasic',
  imports: [MatProgressSpinnerModule, MatCardModule, CommonModule],
  templateUrl: './weatherbasic.component.html',
  styleUrl: './weatherbasic.component.scss'
})
export class WeatherbasicComponent implements OnInit, OnDestroy {
  @ViewChild('lottieContainer', { static: false }) lottieContainer!: ElementRef;
  isLoading = signal(true);
  weatherData = signal<WeatherBasic | null>(null);
  errorMessage = signal<string | null>(null);

  private anim?: AnimationItem;
  private weatherService = inject(WeatherReaderService);
  private destroy$ = new Subject<void>();

  ngOnInit() {
    this.init();
  }

  ngOnDestroy() {
    this.destroy$.next();
    this.destroy$.complete();
    if (this.anim) {
      this.anim.destroy();
    }
  }

  init(): void {
    // 5 minutes in milliseconds = 5 * 60 * 1000 = 300000
    const refreshInterval = 300000;
    timer(0, refreshInterval).pipe(
      tap(() => {
        this.isLoading.set(true);
        this.errorMessage.set(null);
      }),
      switchMap(() => this.weatherService.getLocalCoordinates()),
      switchMap(coords => this.weatherService.getCurrentWeather(coords.latitude, coords.longitude)),
      tap((data) => this.showWeatherData(data)),
      takeUntil(this.destroy$),
    ).subscribe({
      error: (err) => {
        this.errorMessage.set('Unable to load weather right now. Please try again shortly.');
        console.error(this.errorMessage());
        console.error('Failed to load weather data:', err);
        this.isLoading.set(false);
      }
    });
  }

  private showWeatherData(weatherData: WeatherBasic): void {
    this.weatherData.set(weatherData);
    this.errorMessage.set(null);
    this.isLoading.set(false);

    // Wait for the view to update before loading animation
    setTimeout(() => {
      if (this.lottieContainer) {
        if (this.anim) {
          this.anim.destroy();
        }
        this.anim = lottie.loadAnimation({
          container: this.lottieContainer.nativeElement,
          renderer: 'svg',
          loop: true,
          autoplay: true,
          path: weatherData.animationPath
        });
      }
    }, 1);
  }
}
