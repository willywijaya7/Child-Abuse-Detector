import React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import { MaterialCommunityIcons, FontAwesome5 } from '@expo/vector-icons';

interface Props {
  type: string;
  showLabel?: boolean;
}

export default function ActivityIcon({ type="idle", showLabel = true }: Props) {
  const size = 36;
  const color = type === 'falling' ? 'red' : '#000';

  const icon = (() => {
    switch (type) {
      case 'running':
        return <MaterialCommunityIcons name="run" size={size} color={color} />;
      case 'walking':
        return <MaterialCommunityIcons name="walk" size={size} color={color} />;
      case 'sitting':
        return <MaterialCommunityIcons name="seat" size={size} color={color} />;
      case 'standing':
        return <MaterialCommunityIcons name="human" size={size} color={color} />;
      case 'lying':
        return <FontAwesome5 name="bed" size={size} color={color} />;
      case 'idle':
        return <MaterialCommunityIcons name="pause-circle-outline" size={size} color={color} />;
      case 'falling':
        return <MaterialCommunityIcons name="arrow-collapse-down" size={size} color={color} />;
      default:
        return null;
    }
  })();

  return (
    <View style={styles.container}>
      {icon}
      {showLabel && <Text style={[styles.label, { color }]}>{capitalize(type)}</Text>}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    alignItems: 'center',
    justifyContent: 'center',
    marginVertical: 8,
  },
  label: {
    marginTop: 4,
    fontSize: 14,
    fontWeight: '600',
  },
});

function capitalize(text: string) {
  return text.charAt(0).toUpperCase() + text.slice(1);
}
