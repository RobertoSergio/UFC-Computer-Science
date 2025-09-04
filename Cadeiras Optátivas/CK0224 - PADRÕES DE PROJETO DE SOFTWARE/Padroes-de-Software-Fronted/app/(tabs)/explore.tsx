// gen/app/(tabs)/explore.tsx

import Ionicons from '@expo/vector-icons/Ionicons';
import { StyleSheet, Text, Image, View, Dimensions, TouchableOpacity, ActivityIndicator } from 'react-native';
import React from 'react';
import ParallaxScrollView from '@/components/ParallaxScrollView';
import { ThemedText } from '@/components/ThemedText';
import { ThemedView } from '@/components/ThemedView';
import { useExploreViewModel } from '@/viewmodels/useExploreViewModel';

export default function ExploreScreen() {
  const { user, isLoading, handleLogout } = useExploreViewModel();

  const renderContent = () => {
    if (isLoading) {
      return <ActivityIndicator size="large" style={styles.centered} />;
    }

    if (!user) {
      return <Text style={styles.emptyMessage}>Não foi possível carregar os dados do usuário.</Text>;
    }

    return (
      <View style={styles.container}>
        <View style={styles.userInfoCard}>
          <Ionicons name="person-outline" size={24} color="black" />
          <Text style={styles.infoText}>{user.fullName}</Text>
        </View>
        <View style={styles.userInfoCard}>
          <Ionicons name="mail-outline" size={24} color="black" />
          <Text style={styles.infoText}>{user.email}</Text>
        </View>
        <View style={styles.userInfoCard}>
          <Ionicons name="card-outline" size={24} color="black" />
          <Text style={styles.infoText}>CPF: {user.cpf}</Text>
        </View>
        <View style={styles.userInfoCard}>
          <Ionicons name="location-outline" size={24} color="black" />
          <Text style={styles.infoText}>{user.location}</Text>
        </View>

        <TouchableOpacity style={styles.logoutButton} onPress={handleLogout}>
          <Ionicons name="log-out-outline" size={22} color="white" />
          <Text style={styles.logoutButtonText}>Sair</Text>
        </TouchableOpacity>
      </View>
    );
  };

  return (
    <ParallaxScrollView
      headerBackgroundColor={{ light: '#F0F0F0', dark: '#353636' }}
      headerImage={<Image source={require('@/assets/images/foto_perfil.jpg')} style={styles.headerImage} />}
    >
      <ThemedView style={styles.titleContainer}>
        <ThemedText type="title">Minha Conta</ThemedText>
      </ThemedView>
      {renderContent()}
    </ParallaxScrollView>
  );
}

const { width } = Dimensions.get('window');

const styles = StyleSheet.create({
  container: {
    alignItems: 'center',
    paddingVertical: 20,
  },
  centered: {
    marginTop: 50,
  },
  headerImage: {
    width: '100%',
    height: 220,
  },
  titleContainer: {
    alignItems: 'center',
    gap: 8,
  },
  userInfoCard: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: '#ffffff',
    padding: 15,
    borderRadius: 10,
    width: width * 0.9,
    marginBottom: 12,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 3,
    elevation: 3,
  },
  infoText: {
    fontSize: 16,
    marginLeft: 15,
  },
  emptyMessage: {
    textAlign: 'center',
    fontSize: 16,
    color: 'gray',
    marginTop: 40,
  },
  logoutButton: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#d9534f',
    paddingVertical: 12,
    paddingHorizontal: 25,
    borderRadius: 8,
    marginTop: 30,
  },
  logoutButtonText: {
    color: 'white',
    marginLeft: 8,
    fontSize: 16,
    fontWeight: 'bold',
  },
});