import { createSlice } from '@reduxjs/toolkit';

const initialState = {
  dailyUsage: [],
  weeklyStats: {
    totalOpens: 0,
    averageLevel: 0,
    peakHours: [],
  },
  monthlyReport: {
    totalOpens: 0,
    averageFillTime: 0,
    mostActiveDay: '',
  },
  isLoading: false,
  error: null,
};

const analyticsSlice = createSlice({
  name: 'analytics',
  initialState,
  reducers: {
    addUsageEntry: (state, action) => {
      const entry = {
        timestamp: new Date().toISOString(),
        action: action.payload.action,
        duration: action.payload.duration || 0,
        trashLevel: action.payload.trashLevel || 0,
      };

      state.dailyUsage.push(entry);

      // Keep only last 100 entries
      if (state.dailyUsage.length > 100) {
        state.dailyUsage = state.dailyUsage.slice(-100);
      }

      // Update weekly stats
      state.weeklyStats.totalOpens += 1;
    },
    updateWeeklyStats: (state, action) => {
      state.weeklyStats = { ...state.weeklyStats, ...action.payload };
    },
    updateMonthlyReport: (state, action) => {
      state.monthlyReport = { ...state.monthlyReport, ...action.payload };
    },
    setLoading: (state, action) => {
      state.isLoading = action.payload;
    },
    setError: (state, action) => {
      state.error = action.payload;
    },
    resetAnalytics: () => initialState,
  },
});

export const {
  addUsageEntry,
  updateWeeklyStats,
  updateMonthlyReport,
  setLoading,
  setError,
  resetAnalytics,
} = analyticsSlice.actions;

export default analyticsSlice.reducer;
