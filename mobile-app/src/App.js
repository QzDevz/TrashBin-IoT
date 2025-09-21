import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import { Provider as PaperProvider } from 'react-native-paper';
import { Provider as ReduxProvider } from 'react-redux';
import { SafeAreaProvider } from 'react-native-safe-area-context';
import Icon from 'react-native-vector-icons/MaterialIcons';

import { store } from './store/store';
import DashboardScreen from './screens/DashboardScreen';
import ControlScreen from './screens/ControlScreen';
import AnalyticsScreen from './screens/AnalyticsScreen';
import SettingsScreen from './screens/SettingsScreen';
import { theme } from './utils/theme';

const Tab = createBottomTabNavigator();

const App = () => {
  return (
    <ReduxProvider store={store}>
      <PaperProvider theme={theme}>
        <SafeAreaProvider>
          <NavigationContainer>
            <Tab.Navigator
              screenOptions={({ route }) => ({
                tabBarIcon: ({ focused, color, size }) => {
                  let iconName;

                  if (route.name === 'Dashboard') {
                    iconName = 'dashboard';
                  } else if (route.name === 'Control') {
                    iconName = 'settings-remote';
                  } else if (route.name === 'Analytics') {
                    iconName = 'analytics';
                  } else if (route.name === 'Settings') {
                    iconName = 'settings';
                  }

                  return <Icon name={iconName} size={size} color={color} />;
                },
                tabBarActiveTintColor: theme.colors.primary,
                tabBarInactiveTintColor: 'gray',
                headerStyle: {
                  backgroundColor: theme.colors.primary,
                },
                headerTintColor: '#fff',
                headerTitleStyle: {
                  fontWeight: 'bold',
                },
              })}
            >
              <Tab.Screen
                name="Dashboard"
                component={DashboardScreen}
                options={{ title: 'Smart Trashcan' }}
              />
              <Tab.Screen
                name="Control"
                component={ControlScreen}
                options={{ title: 'Remote Control' }}
              />
              <Tab.Screen
                name="Analytics"
                component={AnalyticsScreen}
                options={{ title: 'Usage Analytics' }}
              />
              <Tab.Screen
                name="Settings"
                component={SettingsScreen}
                options={{ title: 'Settings' }}
              />
            </Tab.Navigator>
          </NavigationContainer>
        </SafeAreaProvider>
      </PaperProvider>
    </ReduxProvider>
  );
};

export default App;
