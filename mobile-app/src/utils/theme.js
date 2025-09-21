import { DefaultTheme } from 'react-native-paper';

export const theme = {
  ...DefaultTheme,
  colors: {
    ...DefaultTheme.colors,
    primary: '#2196F3',
    primaryContainer: '#E3F2FD',
    secondary: '#FFC107',
    secondaryContainer: '#FFF8E1',
    tertiary: '#4CAF50',
    tertiaryContainer: '#E8F5E8',
    error: '#F44336',
    errorContainer: '#FFEBEE',
    background: '#FAFAFA',
    surface: '#FFFFFF',
    surfaceVariant: '#F5F5F5',
    onPrimary: '#FFFFFF',
    onSecondary: '#000000',
    onTertiary: '#FFFFFF',
    onError: '#FFFFFF',
    onBackground: '#000000',
    onSurface: '#000000',
    onSurfaceVariant: '#666666',
    outline: '#BDBDBD',
    outlineVariant: '#E0E0E0',
    shadow: '#000000',
    scrim: '#000000',
    inverseSurface: '#121212',
    inverseOnSurface: '#FFFFFF',
    inversePrimary: '#64B5F6',
    elevation: {
      level0: 'transparent',
      level1: '#FFFFFF',
      level2: '#F5F5F5',
      level3: '#E0E0E0',
      level4: '#BDBDBD',
      level5: '#9E9E9E',
    },
    surfaceDisabled: '#FAFAFA',
    onSurfaceDisabled: '#9E9E9E',
  },
  roundness: 8,
  animation: {
    scale: 1.0,
  },
  version: 3,
};

// Custom component styles
export const componentStyles = {
  card: {
    elevation: 4,
    margin: 8,
    borderRadius: 12,
  },
  button: {
    primary: {
      backgroundColor: theme.colors.primary,
      borderRadius: 8,
      paddingVertical: 12,
      paddingHorizontal: 24,
    },
    secondary: {
      backgroundColor: theme.colors.secondary,
      borderRadius: 8,
      paddingVertical: 12,
      paddingHorizontal: 24,
    },
  },
  text: {
    title: {
      fontSize: 24,
      fontWeight: 'bold',
      color: theme.colors.onSurface,
      marginBottom: 16,
    },
    subtitle: {
      fontSize: 18,
      fontWeight: '600',
      color: theme.colors.onSurfaceVariant,
      marginBottom: 8,
    },
    body: {
      fontSize: 16,
      color: theme.colors.onSurface,
      lineHeight: 24,
    },
    caption: {
      fontSize: 14,
      color: theme.colors.onSurfaceVariant,
    },
  },
  spacing: {
    xs: 4,
    sm: 8,
    md: 16,
    lg: 24,
    xl: 32,
    xxl: 48,
  },
  borderRadius: {
    sm: 4,
    md: 8,
    lg: 12,
    xl: 16,
    xxl: 24,
  },
};

// Utility functions for consistent styling
export const getStatusColor = (status) => {
  switch (status) {
    case 'connected':
    case 'online':
    case 'open':
      return theme.colors.tertiary;
    case 'disconnected':
    case 'offline':
    case 'closed':
      return theme.colors.onSurfaceVariant;
    case 'error':
    case 'full':
      return theme.colors.error;
    case 'warning':
    case 'half':
      return theme.colors.secondary;
    default:
      return theme.colors.primary;
  }
};

export const getStatusIcon = (status) => {
  switch (status) {
    case 'connected':
    case 'online':
      return 'wifi';
    case 'disconnected':
    case 'offline':
      return 'wifi-off';
    case 'open':
      return 'lid';
    case 'closed':
      return 'lid-closed';
    case 'error':
      return 'error';
    case 'warning':
      return 'warning';
    case 'full':
      return 'delete-full';
    case 'half':
      return 'delete-half';
    default:
      return 'info';
  }
};

export default theme;
