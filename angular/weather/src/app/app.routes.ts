import { Routes } from '@angular/router';
import { WeatherbasicComponent } from './shared/weatherbasic/weatherbasic.component';

export const routes: Routes = [
    { path: '', redirectTo: '/home', pathMatch: 'full' },
    { path: 'home', component: WeatherbasicComponent }
];
