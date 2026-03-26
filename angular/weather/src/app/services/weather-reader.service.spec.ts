import { TestBed } from '@angular/core/testing';

import { WeatherReaderService } from './weather-reader.service';

describe('WeatherReaderService', () => {
  let service: WeatherReaderService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(WeatherReaderService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
