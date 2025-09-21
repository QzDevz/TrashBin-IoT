import React, { useEffect } from 'react';
import { View, StyleSheet, ScrollView, RefreshControl } from 'react-native';
import { Card, Title, Paragraph, Button, Chip, ActivityIndicator } from 'react-native-paper';
import { useSelector, useDispatch } from 'react-redux';
import Icon from 'react-native-vector-icons/MaterialIcons';

import { updateStatus, setLoading } from '../store/slices/deviceSlice';
import { theme } from '../utils/theme';

const DashboardScreen = () => {
  const dispatch = useDispatch();
  const { status, isConnected, isLoading, deviceInfo } = useSelector(state => state.device);
  const [refreshing, setRefreshing] = React.useState(false);

  const onRefresh = async () => {
    setRefreshing(true);
    dispatch(setLoading(true));
    // Simulate API call
    setTimeout(() => {
      dispatch(updateStatus({
        lidOpen: Math.random() > 0.5,
        trashLevel: Math.floor(Math.random() * 100),
      }));
      dispatch(setLoading(false));
      setRefreshing(false);
    }, 1000);
  };

  const getTrashLevelColor = (level) => {
    if (level < 30) return '#4CAF50'; // Green
    if (level < 70) return '#FF9800'; // Orange
    return '#F44336'; // Red
  };

  const getTrashLevelText = (level) => {
    if (level < 30) return 'Empty';
    if (level < 70) return 'Half Full';
    return 'Full';
  };

  return (
    <ScrollView
      style={styles.container}
      refreshControl={
        <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
      }
    >
      <View style={styles.header}>
        <Title style={styles.title}>Smart Trashcan Dashboard</Title>
        <Chip
          icon={isConnected ? 'wifi' : 'wifi-off'}
          mode={isConnected ? 'flat' : 'outlined'}
          style={{ backgroundColor: isConnected ? '#4CAF50' : '#F44336' }}
        >
          {isConnected ? 'Connected' : 'Disconnected'}
        </Chip>
      </View>

      {isLoading ? (
        <ActivityIndicator animating={true} size="large" style={styles.loader} />
      ) : (
        <View style={styles.content}>
          {/* Device Status Card */}
          <Card style={styles.card}>
            <Card.Content>
              <View style={styles.cardHeader}>
                <Icon name="device-hub" size={24} color={theme.colors.primary} />
                <Title style={styles.cardTitle}>Device Status</Title>
              </View>
              <View style={styles.statusRow}>
                <View style={styles.statusItem}>
                  <Icon name="lid" size={20} color={status.lidOpen ? '#4CAF50' : '#757575'} />
                  <Paragraph style={styles.statusText}>
                    Lid: {status.lidOpen ? 'Open' : 'Closed'}
                  </Paragraph>
                </View>
                <View style={styles.statusItem}>
                  <Icon name="delete" size={20} color={getTrashLevelColor(status.trashLevel)} />
                  <Paragraph style={styles.statusText}>
                    Trash: {getTrashLevelText(status.trashLevel)}
                  </Paragraph>
                </View>
              </View>
            </Card.Content>
          </Card>

          {/* Trash Level Card */}
          <Card style={styles.card}>
            <Card.Content>
              <View style={styles.cardHeader}>
                <Icon name="analytics" size={24} color={theme.colors.primary} />
                <Title style={styles.cardTitle}>Trash Level</Title>
              </View>
              <View style={styles.levelContainer}>
                <View style={styles.levelBar}>
                  <View
                    style={[
                      styles.levelFill,
                      {
                        width: `${status.trashLevel}%`,
                        backgroundColor: getTrashLevelColor(status.trashLevel),
                      },
                    ]}
                  />
                </View>
                <Paragraph style={styles.levelText}>
                  {status.trashLevel}% Full
                </Paragraph>
              </View>
            </Card.Content>
          </Card>

          {/* Quick Actions Card */}
          <Card style={styles.card}>
            <Card.Content>
              <View style={styles.cardHeader}>
                <Icon name="settings-remote" size={24} color={theme.colors.primary} />
                <Title style={styles.cardTitle}>Quick Actions</Title>
              </View>
              <View style={styles.actionsContainer}>
                <Button
                  mode="contained"
                  icon="lid"
                  onPress={() => {
                    dispatch(updateStatus({ lidOpen: !status.lidOpen }));
                  }}
                  style={styles.actionButton}
                >
                  {status.lidOpen ? 'Close Lid' : 'Open Lid'}
                </Button>
                <Button
                  mode="outlined"
                  icon="refresh"
                  onPress={onRefresh}
                  style={styles.actionButton}
                >
                  Refresh
                </Button>
              </View>
            </Card.Content>
          </Card>

          {/* Device Info Card */}
          <Card style={styles.card}>
            <Card.Content>
              <View style={styles.cardHeader}>
                <Icon name="info" size={24} color={theme.colors.primary} />
                <Title style={styles.cardTitle}>Device Information</Title>
              </View>
              <View style={styles.infoContainer}>
                <View style={styles.infoRow}>
                  <Paragraph style={styles.infoLabel}>Name:</Paragraph>
                  <Paragraph style={styles.infoValue}>{deviceInfo.name}</Paragraph>
                </View>
                <View style={styles.infoRow}>
                  <Paragraph style={styles.infoLabel}>IP Address:</Paragraph>
                  <Paragraph style={styles.infoValue}>{deviceInfo.ip || 'Not connected'}</Paragraph>
                </View>
                <View style={styles.infoRow}>
                  <Paragraph style={styles.infoLabel}>Firmware:</Paragraph>
                  <Paragraph style={styles.infoValue}>v{deviceInfo.firmware}</Paragraph>
                </View>
              </View>
            </Card.Content>
          </Card>
        </View>
      )}
    </ScrollView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#f5f5f5',
  },
  header: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    padding: 16,
    backgroundColor: 'white',
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
  },
  loader: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  content: {
    padding: 16,
  },
  card: {
    marginBottom: 16,
    elevation: 4,
  },
  cardHeader: {
    flexDirection: 'row',
    alignItems: 'center',
    marginBottom: 16,
  },
  cardTitle: {
    marginLeft: 8,
    fontSize: 18,
  },
  statusRow: {
    flexDirection: 'row',
    justifyContent: 'space-around',
  },
  statusItem: {
    alignItems: 'center',
  },
  statusText: {
    marginTop: 4,
    fontSize: 14,
  },
  levelContainer: {
    alignItems: 'center',
  },
  levelBar: {
    width: '100%',
    height: 20,
    backgroundColor: '#e0e0e0',
    borderRadius: 10,
    overflow: 'hidden',
  },
  levelFill: {
    height: '100%',
    borderRadius: 10,
  },
  levelText: {
    marginTop: 8,
    fontSize: 16,
    fontWeight: 'bold',
  },
  actionsContainer: {
    flexDirection: 'row',
    justifyContent: 'space-around',
    marginTop: 8,
  },
  actionButton: {
    flex: 1,
    marginHorizontal: 8,
  },
  infoContainer: {
    marginTop: 8,
  },
  infoRow: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    paddingVertical: 4,
  },
  infoLabel: {
    fontWeight: 'bold',
  },
  infoValue: {
    color: '#666',
  },
});

export default DashboardScreen;
