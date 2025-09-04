// gen/app/estabelecimento_info.tsx

import React from 'react';
import { View, Text, TextInput, Button, FlatList, ScrollView, StyleSheet, ActivityIndicator, Platform } from 'react-native';
import { useEstabelecimentoInfoViewModel } from '@/viewmodels/useEstabelecimentoInfoViewModel';

export default function EstabelecimentoDetalhesScreen() {
  const {
    estabelecimento,
    avaliacoes,
    nota,
    setNota,
    descricao,
    setDescricao,
    isLoading,
    isSubmitting,
    error,
    handleAvaliacaoSubmit,
  } = useEstabelecimentoInfoViewModel();

  if (isLoading) {
    return <View style={styles.centered}><ActivityIndicator size="large" /></View>;
  }

  if (error || !estabelecimento) {
    return <View style={styles.centered}><Text style={styles.errorText}>{error || 'Estabelecimento não encontrado.'}</Text></View>;
  }

  const renderInfoRow = (label: string, value: string | boolean | undefined) => (
    <Text style={styles.info}>
      <Text style={styles.infoLabel}>{label}:</Text> {typeof value === 'boolean' ? (value ? 'Sim' : 'Não') : value || 'Não informado'}
    </Text>
  );

  return (
    <ScrollView contentContainerStyle={styles.scrollContainer}>
      <View style={styles.card}>
        <Text style={styles.title}>{estabelecimento.nome_fantasia}</Text>
        {renderInfoRow('Endereço', `${estabelecimento.endereco_estabelecimento}, ${estabelecimento.numero_estabelecimento}`)}
        {renderInfoRow('Bairro', estabelecimento.bairro_estabelecimento)}
        {renderInfoRow('Telefone', estabelecimento.numero_telefone_estabelecimento)}
        {renderInfoRow('Email', estabelecimento.endereco_email_estabelecimento)}
        {renderInfoRow('CEP', estabelecimento.codigo_cep_estabelecimento)}
        
        <Text style={styles.sectionTitle}>Turno de Atendimento</Text>
        <Text style={styles.info}>{estabelecimento.descricao_turno_atendimento}</Text>

        <Text style={styles.sectionTitle}>Detalhes do Serviço</Text>
        {renderInfoRow('Atendimento SUS', estabelecimento.estabelecimento_faz_atendimento_ambulatorial_sus)}
        {renderInfoRow('Centro Cirúrgico', estabelecimento.estabelecimento_possui_centro_cirurgico)}
        {renderInfoRow('Centro Obstétrico', estabelecimento.estabelecimento_possui_centro_obstetrico)}
        {renderInfoRow('UTI Neonatal', estabelecimento.estabelecimento_possui_centro_neonatal)}
        {renderInfoRow('Atendimento Hospitalar', estabelecimento.estabelecimento_possui_atendimento_hospitalar)}
      </View>

      <View style={styles.card}>
        <Text style={styles.sectionTitle}>Avaliações</Text>
        <FlatList
          data={avaliacoes}
          keyExtractor={(item) => item.id.toString()}
          renderItem={({ item }) => (
            <View style={styles.avaliacaoCard}>
              <Text style={styles.avaliacaoNota}>Nota: {item.nota}/5</Text>
              <Text style={styles.avaliacaoDescricao}>{item.descricao}</Text>
            </View>
          )}
          ListEmptyComponent={<Text style={styles.emptyMessage}>Nenhuma avaliação encontrada.</Text>}
          scrollEnabled={false} // Para não ter scroll dentro de scroll
        />
      </View>

      <View style={styles.card}>
        <Text style={styles.sectionTitle}>Deixe sua Avaliação</Text>
        <TextInput style={styles.input} placeholder="Nota (0 a 5)" inputMode="numeric" value={nota} onChangeText={setNota} maxLength={3} />
        <TextInput style={styles.input} placeholder="Descrição da sua experiência" value={descricao} onChangeText={setDescricao} multiline />
        <Button title={isSubmitting ? "Enviando..." : "Enviar Avaliação"} onPress={handleAvaliacaoSubmit} disabled={isSubmitting} />
      </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
    scrollContainer: {
        flexGrow: 1,
        padding: 10,
        backgroundColor: '#f0f2f5',
    },
    centered: {
        flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
    },
    card: {
        backgroundColor: '#fff',
        borderRadius: 8,
        padding: 20,
        marginBottom: 15,
        shadowColor: '#000',
        shadowOffset: { width: 0, height: 1 },
        shadowOpacity: 0.2,
        shadowRadius: 2,
        elevation: 3,

        ...Platform.select({
    ios: {
      shadowColor: '#000',
      shadowOffset: { width: 0, height: 1 },
      shadowOpacity: 0.2,
      shadowRadius: 2,
    },
    android: {
      elevation: 3,
    },
    web: {
      boxShadow: '0px 1px 2px rgba(0, 0, 0, 0.2)',
    }
  }),
    },
    title: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 15,
    },
    info: {
        fontSize: 16,
        marginBottom: 8,
        lineHeight: 22,
    },
    infoLabel: {
        fontWeight: 'bold',
    },
    sectionTitle: {
        fontSize: 20,
        fontWeight: 'bold',
        marginTop: 15,
        marginBottom: 10,
        borderTopColor: '#eee',
        borderTopWidth: 1,
        paddingTop: 15,
    },
    avaliacaoCard: {
        paddingVertical: 10,
        borderBottomWidth: 1,
        borderBottomColor: '#f0f0f0',
    },
    avaliacaoNota: {
        fontSize: 16,
        fontWeight: 'bold',
    },
    avaliacaoDescricao: {
        fontSize: 15,
        color: '#333',
        marginTop: 4,
    },
    emptyMessage: {
        fontSize: 15,
        color: 'gray',
        textAlign: 'center',
        paddingVertical: 10,
    },
    input: {
        backgroundColor: '#f9f9f9',
        borderRadius: 5,
        borderWidth: 1,
        borderColor: '#ddd',
        padding: 10,
        fontSize: 16,
        marginBottom: 10,
    },
    errorText: {
        fontSize: 16,
        color: 'red',
        textAlign: 'center',
    },
});