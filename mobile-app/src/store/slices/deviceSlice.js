import { createSlice } from '@reduxjs/toolkit';

const initialState = {
  isConnected: false,
  deviceInfo: {
    name: 'Smart Trashcan',
    ip: '',
    mac: '',
    firmware: '1.0.0',
  },
  status: {
    lidOpen: false,
    trashLevel: 0, // 0-100 percentage
    lastUpdate: null,
  },
  sensors: {
    handDetected: false,
    distance: 0,
  },
  isLoading: false,
  error: null,
};

const deviceSlice = createSlice({
  name: 'device',
  initialState,
  reducers: {
    setConnectionStatus: (state, action) => {
      state.isConnected = action.payload;
    },
    setDeviceInfo: (state, action) => {
      state.deviceInfo = { ...state.deviceInfo, ...action.payload };
    },
    updateStatus: (state, action) => {
      state.status = { ...state.status, ...action.payload, lastUpdate: new Date().toISOString() };
    },
    updateSensors: (state, action) => {
      state.sensors = { ...state.sensors, ...action.payload };
    },
    setLoading: (state, action) => {
      state.isLoading = action.payload;
    },
    setError: (state, action) => {
      state.error = action.payload;
    },
    resetDevice: () => initialState,
  },
});

export const {
  setConnectionStatus,
  setDeviceInfo,
  updateStatus,
  updateSensors,
  setLoading,
  setError,
  resetDevice,
} = deviceSlice.actions;

export default deviceSlice.reducer;
