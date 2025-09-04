// gen/app/cadastro.tsx

import React from 'react';
import { View, TextInput, Text, Image, Dimensions, TouchableOpacity, StyleSheet, ScrollView, ActivityIndicator } from 'react-native';
import { useRouter } from 'expo-router';
import { useCadastroViewModel } from '@/viewmodels/useCadastroViewModel';

const CadastroScreen = () => {
  const router = useRouter();
  const {
    firstName, setFirstName,
    lastName, setLastName,
    username, setUsername,
    cpf, setCpf,
    email, setEmail,
    password, setPassword,
    confirmPassword, setConfirmPassword,
    city, setCity,
    state, setState,
    isLoading,
    error,
    handleCadastro,
  } = useCadastroViewModel();

  return (
    <ScrollView contentContainerStyle={styles.scrollContainer}>
      <View style={styles.container}>
        <Image
          source={require('@/assets/images/saude_conn_logo.png')}
          style={styles.logo}
        />
        <Text style={styles.title}>Cadastro</Text>

        {error && <Text style={styles.errorText}>{error}</Text>}
        
        <View style={styles.formContainer}>
          <View style={styles.row}>
            <TextInput style={[styles.input, styles.inputHalf]} placeholder="Nome" value={firstName} onChangeText={setFirstName} />
            <TextInput style={[styles.input, styles.inputHalf]} placeholder="Sobrenome" value={lastName} onChangeText={setLastName} />
          </View>
          <TextInput style={styles.input} placeholder="Nome de usuário" value={username} onChangeText={setUsername} />
          <TextInput style={styles.input} placeholder="CPF" value={cpf} onChangeText={setCpf} inputMode="numeric" />
          <TextInput style={styles.input} placeholder="E-mail" value={email} onChangeText={setEmail} keyboardType="email-address" autoCapitalize="none" />
          <TextInput style={styles.input} placeholder="Senha" value={password} secureTextEntry onChangeText={setPassword} />
          <TextInput style={styles.input} placeholder="Confirme sua senha" value={confirmPassword} secureTextEntry onChangeText={setConfirmPassword} />
          <View style={styles.row}>
            <TextInput style={[styles.input, styles.inputHalf]} placeholder="Cidade" value={city} onChangeText={setCity} />
            <TextInput style={[styles.input, styles.inputHalf]} placeholder="Estado" value={state} onChangeText={setState} />
          </View>
        </View>

        <TouchableOpacity style={styles.buttonContainer} onPress={handleCadastro} disabled={isLoading}>
          {isLoading ? <ActivityIndicator color="#fff" /> : <Text style={styles.buttonText}>Cadastrar</Text>}
        </TouchableOpacity>

        <TouchableOpacity onPress={() => router.push('/')}>
          <Text style={styles.signupText}>Já tem conta? <Text style={styles.linkText}>Faça login</Text></Text>
        </TouchableOpacity>
      </View>
    </ScrollView>
  );
};

export default CadastroScreen;

const { width } = Dimensions.get('window');

const styles = StyleSheet.create({
  scrollContainer: {
    flexGrow: 1,
    justifyContent: 'center',
    backgroundColor: '#ffffff',
  },
  container: {
    alignItems: 'center',
    paddingHorizontal: 16,
    paddingVertical: 20,
  },
  title: {
    fontSize: 28,
    marginBottom: 20,
    fontWeight: 'bold',
  },
  logo: {
    width: 250,
    height: 120,
    resizeMode: 'contain',
    marginBottom: 20,
  },
  formContainer: {
    width: '100%',
    maxWidth: 400,
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'space-between',
  },
  input: {
    height: 45,
    borderColor: '#ddd',
    borderWidth: 1,
    borderRadius: 8,
    marginBottom: 12,
    paddingHorizontal: 10,
    backgroundColor: '#f9f9f9',
    width: '100%',
  },
  inputHalf: {
    width: '48%',
  },
  buttonContainer: {
    width: '100%',
    maxWidth: 400,
    height: 50,
    backgroundColor: '#007BFF',
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 8,
    marginTop: 10,
  },
  buttonText: {
    color: 'white',
    fontSize: 18,
    fontWeight: 'bold',
  },
  signupText: {
    marginTop: 20,
    fontSize: 16,
  },
  linkText: {
    color: '#007BFF',
    fontWeight: 'bold',
  },
  errorText: {
    color: 'red',
    marginBottom: 15,
    textAlign: 'center',
    fontWeight: 'bold',
  },
});