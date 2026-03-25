import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WeatherbasicComponent } from './weatherbasic.component';

// Mock lottie-web to avoid canvas errors in tests
jest.mock('lottie-web', () => ({
  __esModule: true,
  default: {
    loadAnimation: jest.fn(() => ({
      destroy: jest.fn(),
      play: jest.fn(),
      stop: jest.fn(),
      pause: jest.fn(),
    })),
  },
}));

describe('WeatherbasicComponent', () => {
  let component: WeatherbasicComponent;
  let fixture: ComponentFixture<WeatherbasicComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [WeatherbasicComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(WeatherbasicComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
