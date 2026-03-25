import { Component, ElementRef, ViewChild, OnInit, OnDestroy, inject, signal } from '@angular/core';
import lottie, { AnimationItem } from 'lottie-web';
import { WeatherReaderService } from '../../services/services/weather-reader.service';
import { WeatherBasic } from '../../models/weather-basic.model';
import { Subject } from 'rxjs';
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

  private anim?: AnimationItem;
  private weatherService = inject(WeatherReaderService);

  ngOnInit() {
    this.weatherService.getLocalCoordinates().subscribe({
      next: (coords) => {
        console.log('User coordinates:', coords);
        this.getCurrentWeather(coords.latitude, coords.longitude);
      },
      error: (err) => {
        console.error('Error getting location:', err);
        this.isLoading.set(false);
      }
    });
  }

  ngOnDestroy() {
    if (this.anim) {
      this.anim.destroy();
    }
  }

  getCurrentWeather(lat: number, lon: number) {
    this.weatherService.getCurrentWeather(lat, lon).subscribe(weatherData => {
      this.weatherData.set(weatherData);
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
    });
  }

}
