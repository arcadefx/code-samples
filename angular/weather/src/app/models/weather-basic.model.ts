export interface WeatherBasic {
  temperature: number;
  condition: string;
  humidity: number;
  wind: number;
  windDirection?: string;
  city: string;
  animationPath: string;
}
