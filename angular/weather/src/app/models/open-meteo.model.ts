export interface OpenMeteoResponse {
  latitude: number;
  longitude: number;
  generationtime_ms: number;
  utc_offset_seconds: number;
  timezone: string;
  timezone_abbreviation: string;
  elevation: number;
  current_units: CurrentUnits;
  current: CurrentWeather;
}

export interface CurrentUnits {
  time: string;
  interval: string;
  temperature_2m: string;
  relative_humidity_2m?: string;
  apparent_temperature?: string;
  is_day?: string;
  precipitation?: string;
  weather_code: string;
  cloud_cover?: string;
  wind_speed_10m?: string;
  wind_direction_10m?: string;
}

export interface CurrentWeather {
  time: string;
  interval: number;
  temperature_2m: number;
  relative_humidity_2m?: number;
  apparent_temperature?: number;
  is_day?: number;
  precipitation?: number;
  weather_code: number;
  cloud_cover?: number;
  wind_speed_10m?: number;
  wind_direction_10m?: number;
}

/**
 * WMO Weather interpretation codes (WW)
 * https://open-meteo.com/en/docs
 */
export enum WeatherCode {
  ClearSky = 0,
  MainlyClear = 1,
  PartlyCloudy = 2,
  Overcast = 3,
  Fog = 45,
  DepositingRimeFog = 48,
  DrizzleLight = 51,
  DrizzleModerate = 53,
  DrizzleDense = 55,
  FreezingDrizzleLight = 56,
  FreezingDrizzleDense = 57,
  RainSlight = 61,
  RainModerate = 63,
  RainHeavy = 65,
  FreezingRainLight = 66,
  FreezingRainHeavy = 67,
  SnowFallSlight = 71,
  SnowFallModerate = 73,
  SnowFallHeavy = 75,
  SnowGrains = 77,
  RainShowersSlight = 80,
  RainShowersModerate = 81,
  RainShowersViolent = 82,
  SnowShowersSlight = 85,
  SnowShowersHeavy = 86,
  Thunderstorm = 95,
  ThunderstormSlightHail = 96,
  ThunderstormHeavyHail = 99
}
