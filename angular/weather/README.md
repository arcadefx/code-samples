# Weather App

An Angular weather app that uses your browser location to load current local weather conditions, reverse-geocodes the coordinates into a place name, and displays a matching Lottie animation for the current conditions.

## Features

- Uses browser geolocation to detect the current latitude and longitude
- Fetches current weather data from Open-Meteo
- Resolves the current city or local area using OpenStreetMap Nominatim reverse geocoding
- Displays temperature, condition, wind speed, and humidity
- Maps weather codes to animated weather scenes stored in `public/assets`
- Built with Angular standalone components and Angular Material

## Tech Stack

- Angular 19
- TypeScript
- Angular Material
- RxJS
- lottie-web
- Jest for unit tests

## How It Works

1. The app redirects `/` to `/home`.
2. The weather component asks the browser for geolocation access.
3. The app requests current weather data from Open-Meteo.
4. The app requests a city or locality name from Nominatim.
5. The UI renders the weather details and loads a matching animation.

## Prerequisites

- Node.js 18+ recommended
- npm
- A browser with geolocation enabled

## Getting Started

Install dependencies:

```bash
npm install
```

Start the development server:

```bash
npm start
```

Open the app at:

```text
http://localhost:4200
```

When prompted by the browser, allow location access. Without geolocation permission, the app cannot fetch local weather data.

## Available Scripts

Run the dev server:

```bash
npm start
```

Create a production build:

```bash
npm run build
```

## Project Structure

```text
src/
	app/
		app.config.ts                 Application bootstrap providers
		app.routes.ts                 Route configuration
		models/                       Shared data and mapping models
		services/services/            Weather and geolocation data access
		shared/weatherbasic/          Main weather UI component
public/assets/                   Lottie weather animation files
```

## External Services

The app currently depends on these public APIs:

- Open-Meteo for current weather data
- OpenStreetMap Nominatim for reverse geocoding

Neither service is configured through environment files in this project at the moment. No API keys are utilized.

## Notes

- Weather values are shown in Fahrenheit and mph
- The current implementation focuses on current conditions only
- The app uses local animation JSON files rather than loading animations from a third-party CDN

## Testing

This project is set up to run unit tests with Jest.

Current test coverage is minimal and mostly checks component and service creation. If you expand the app, useful next tests would cover:

- geolocation success and failure paths
- API response mapping to `WeatherBasic`
- weather code to animation mapping
- UI states for loading, success, and error handling
