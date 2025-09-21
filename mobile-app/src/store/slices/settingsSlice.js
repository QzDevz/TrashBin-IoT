import { createSlice } from '@reduxjs/toolkit';

const initialState = {
  theme: 'light',
  notifications: {
    enabled: true,
    lidOpen: true,
    trashFull: true,
    deviceOffline: true,
  },
  device: {
    autoConnect: true,
    connectionTimeout: 5000,
    retryAttempts: 3,
  },
  analytics: {
    enabled: true,
    dataRetention: 30, // days
  },
  language: 'en',
  units: {
    distance: 'cm',
    temperature: 'celsius',
  },
};

const settingsSlice = createSlice({
  name: 'settings',
  initialState,
  reducers: {
    updateTheme: (state, action) => {
      state.theme = action.payload;
    },
    updateNotifications: (state, action) => {
      state.notifications = { ...state.notifications, ...action.payload };
    },
    updateDeviceSettings: (state, action) => {
      state.device = { ...state.device, ...action.payload };
    },
    updateAnalyticsSettings: (state, action) => {
      state.analytics = { ...state.analytics, ...action.payload };
    },
    updateLanguage: (state, action) => {
      state.language = action.payload;
    },
    updateUnits: (state, action) => {
      state.units = { ...state.units, ...action.payload };
    },
    resetSettings: () => initialState,
  },
});

export const {
  updateTheme,
  updateNotifications,
  updateDeviceSettings,
  updateAnalyticsSettings,
  updateLanguage,
  updateUnits,
  resetSettings,
} = settingsSlice.actions;

export default settingsSlice.reducer;
