import { Injectable, inject } from '@angular/core';
import { Observable, forkJoin, map } from 'rxjs';
import { HttpClient } from '@angular/common/http';
import { Coords } from '../../models/coords.model';
import { WeatherCode } from '../../models/open-meteo.model';
import { WeatherBasic } from '../../models/weather-basic.model';
import { WeatherAnimations } from '../../models/weather-animations.model';

@Injectable({
  providedIn: 'root'
})
export class WeatherReaderService {
  private http = inject(HttpClient);

  getCurrentWeather(lat: number, lon: number): Observable<WeatherBasic> {
    return forkJoin({
      weather: this.http.get(`https://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lon}&current=temperature_2m,weather_code,relative_humidity_2m,wind_speed_10m&temperature_unit=fahrenheit&wind_speed_unit=mph&timezone=auto`),
      city: this.getCityName(lat, lon)
    }).pipe(
      map(({ weather, city }) => {
        console.log('Weather API response:', weather);
        const weatherCode = (weather as any).current.weather_code;
        const animationPath = this.getWeatherAnimation(weatherCode);
        const conditionKey = WeatherCode[weatherCode];
        return {
          temperature: (weather as any).current.temperature_2m,
          condition: this.formatWeatherCondition(conditionKey),
          humidity: (weather as any).current.relative_humidity_2m,
          wind: (weather as any).current.wind_speed_10m,
          city: city,
          animationPath
        };
      })
    );
  }

  getLocalCoordinates(): Observable<Coords> {
    return new Observable((observer) => {
      if ('geolocation' in navigator) {
        navigator.geolocation.getCurrentPosition(
          (position) => {
            observer.next({
              latitude: position.coords.latitude,
              longitude: position.coords.longitude,
            });
            observer.complete();
          },
          (error) => {
            observer.error(error.message);
          }
        );
      } else {
        observer.error('Geolocation is not supported by your browser');
      }
    });
  }

  getCityName(lat: number, lon: number): Observable<string> {
    return this.http.get(`https://nominatim.openstreetmap.org/reverse?format=jsonv2&lat=${lat}&lon=${lon}`).pipe(
      map((data: any) => {
        console.log('Reverse geocoding response:', data);
        return data.address.city ||
          data.address.town ||
          data.address.village ||
          data.address.suburb ||
          data.address.municipality ||
          data.address.county ||
          'Unknown location';
      })
    );
  }

  getWeatherAnimation(weatherCode: number): string {
    switch (weatherCode) {
      case WeatherCode.ClearSky:
      case WeatherCode.MainlyClear:
        return WeatherAnimations['clear-day'];
      case WeatherCode.PartlyCloudy:
        return WeatherAnimations['partly-cloudy-day'];
      case WeatherCode.Overcast:
        return WeatherAnimations['cloudy'];
      case WeatherCode.Fog:
      case WeatherCode.DepositingRimeFog:
        return WeatherAnimations['fog'];
      case WeatherCode.DrizzleLight:
      case WeatherCode.DrizzleModerate:
      case WeatherCode.DrizzleDense:
      case WeatherCode.FreezingDrizzleLight:
      case WeatherCode.FreezingDrizzleDense:
      case WeatherCode.RainSlight:
      case WeatherCode.RainModerate:
      case WeatherCode.RainHeavy:
      case WeatherCode.FreezingRainLight:
      case WeatherCode.FreezingRainHeavy:
        return WeatherAnimations['rain'];
      case WeatherCode.SnowFallSlight:
      case WeatherCode.SnowFallModerate:
      case WeatherCode.SnowFallHeavy:
        return WeatherAnimations['snow'];
      case WeatherCode.Thunderstorm:
      case WeatherCode.ThunderstormHeavyHail:
      case WeatherCode.ThunderstormSlightHail:
        return WeatherAnimations['thunderstorm'];
      default:
        return WeatherAnimations['clear-day']; // Default animation for unhandled weather codes, can be improved to cover more cases
    }
  }

  private formatWeatherCondition(conditionKey: string | undefined): string {
    if (!conditionKey) {
      return 'Unknown';
    }

    return conditionKey.replace(/([a-z])([A-Z])/g, '$1 $2');
  }

}
