import React from 'react';
import { View, StyleSheet } from 'react-native';
import { Card, Title, Paragraph, Chip } from 'react-native-paper';
import { useSelector } from 'react-redux';
import Icon from 'react-native-vector-icons/MaterialIcons';

import { theme } from '../utils/theme';

const DeviceCard = () => {
  const { status, isConnected } = useSelector(state => state.device);

  const getStatusColor = (connected) => {
    return connected ? theme.colors.tertiary : theme.colors.onSurfaceVariant;
  };

  const getStatusIcon = (connected) => {
    return connected ? 'wifi' : 'wifi-off';
  };

  return (
    <Card style={styles.card}>
      <Card.Content>
        <View style={styles.header}>
          <Icon name="device-hub" size={24} color={theme.colors.primary} />
          <Title style={styles.title}>Smart Trashcan</Title>
          <Chip
            icon={getStatusIcon(isConnected)}
            style={{ backgroundColor: getStatusColor(isConnected) }}
          >
            {isConnected ? 'Connected' : 'Disconnected'}
          </Chip>
        </View>

        <View style={styles.statusContainer}>
          <View style={styles.statusRow}>
            <Icon name="lid" size={20} color={status.lidOpen ? '#4CAF50' : '#757575'} />
            <Paragraph style={styles.statusText}>
              Lid: {status.lidOpen ? 'Open' : 'Closed'}
            </Paragraph>
          </View>

          <View style={styles.statusRow}>
            <Icon name="delete" size={20} color={status.trashLevel < 70 ? '#4CAF50' : '#F44336'} />
            <Paragraph style={styles.statusText}>
              Trash: {status.trashLevel}% Full
            </Paragraph>
          </View>
        </View>
      </Card.Content>
    </Card>
  );
};

const styles = StyleSheet.create({
  card: {
    margin: 16,
    elevation: 4,
  },
  header: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    marginBottom: 16,
  },
  title: {
    flex: 1,
    marginLeft: 8,
    fontSize: 18,
  },
  statusContainer: {
    marginTop: 8,
  },
  statusRow: {
    flexDirection: 'row',
    alignItems: 'center',
    marginVertical: 4,
  },
  statusText: {
    marginLeft: 8,
    fontSize: 14,
  },
});

export default DeviceCard;
