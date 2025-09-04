// gen/app/(tabs)/home.tsx

import { Image, StyleSheet, Text, TextInput, View, FlatList, TouchableOpacity, ActivityIndicator } from 'react-native';
import React from 'react';
import { useHomeViewModel } from '@/viewmodels/useHomeViewModel';

export default function HomeScreen() {
  // A View agora é limpa e apenas consome o hook
  const {
    search,
    isLoading,
    error,
    filteredEstablishments,
    searchFilter,
    handleDetailsPress,
    handleOpenGoogleMaps,
  } = useHomeViewModel();

  // Componente para renderizar o estado de carregamento
  const renderLoading = () => (
    <View style={styles.centered}>
      <ActivityIndicator size="large" color="#007BFF" />
      <Text>Carregando unidades...</Text>
    </View>
  );

  // Componente para renderizar o estado de erro
  const renderError = () => (
    <View style={styles.centered}>
      <Text style={styles.errorText}>Erro: {error}</Text>
    </View>
  );

  // Componente principal da lista
  const renderList = () => (
    <>
      <TextInput
        style={styles.searchBar}
        placeholder="Buscar unidades de saúde..."
        onChangeText={searchFilter}
        value={search}
      />
      <FlatList
        data={filteredEstablishments}
        keyExtractor={(item) => item.id.toString()}
        renderItem={({ item }) => (
          <View style={styles.listItem}>
            <Text style={styles.title}>{item.nome_fantasia}</Text>
            <Text style={styles.subtitle}>Endereço: {item.endereco_estabelecimento}, {item.numero_estabelecimento}</Text>
            <Text style={styles.subtitle}>Telefone: {item.numero_telefone_estabelecimento}</Text>
            <View style={styles.buttonContainer}>
              <TouchableOpacity style={styles.detailsButton} onPress={() => handleDetailsPress(item)}>
                <Text style={styles.buttonText}>Ver mais</Text>
              </TouchableOpacity>
              <TouchableOpacity
                style={styles.routeButton}
                onPress={() => handleOpenGoogleMaps(
                  item.latitude_estabelecimento_decimo_grau,
                  item.longitude_estabelecimento_decimo_grau
                )}
              >
                <Text style={styles.buttonText}>Ver no mapa</Text>
              </TouchableOpacity>
            </View>
          </View>
        )}
        ListEmptyComponent={<Text style={styles.emptyMessage}>Nenhuma unidade encontrada.</Text>}
        contentContainerStyle={{ paddingBottom: 20 }}
      />
    </>
  );

  return (
    <View style={styles.container}>
      <Image
        source={require('@/assets/images/saude_conn_logo.png')}
        style={styles.logo}
        resizeMode="contain" // Agora é uma prop direta
      />
      {isLoading ? renderLoading() : error ? renderError() : renderList()}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingHorizontal: 10,
    backgroundColor: '#fff',
  },
  centered: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  logo: {
    height: 100, // Altura ajustada
    width: '80%',
    alignSelf: 'center',
    resizeMode: 'contain',
    marginVertical: 10,
  },
  searchBar: {
    height: 45,
    borderColor: '#ddd',
    borderWidth: 1,
    borderRadius: 8,
    marginBottom: 15,
    paddingHorizontal: 10,
    backgroundColor: '#f9f9f9',
  },
  listItem: {
    padding: 15,
    borderBottomWidth: 1,
    borderBottomColor: '#eee',
    marginBottom: 10,
    backgroundColor: '#fff',
    borderRadius: 8,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.1,
    shadowRadius: 2,
    elevation: 2,
  },
  title: {
    fontSize: 18,
    fontWeight: 'bold',
  },
  subtitle: {
    fontSize: 14,
    color: '#555',
    marginTop: 4,
  },
  buttonContainer: {
    flexDirection: 'row',
    marginTop: 15,
  },
  detailsButton: {
    backgroundColor: '#3498db',
    paddingVertical: 8,
    paddingHorizontal: 12,
    borderRadius: 5,
    marginRight: 10,
  },
  routeButton: {
    backgroundColor: '#2ecc71',
    paddingVertical: 8,
    paddingHorizontal: 12,
    borderRadius: 5,
  },
  buttonText: {
    color: '#fff',
    fontSize: 14,
    fontWeight: 'bold',
  },
  emptyMessage: {
    textAlign: 'center',
    marginTop: 50,
    fontSize: 16,
    color: 'gray',
  },
  errorText: {
    color: 'red',
    fontSize: 16,
  }
});