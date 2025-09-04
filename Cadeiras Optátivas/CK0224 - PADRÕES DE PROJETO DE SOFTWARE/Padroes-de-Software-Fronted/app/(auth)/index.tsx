// gen/app/(auth)/index.tsx

import React from 'react';
import { View, TextInput, StyleSheet, Text, Image, Dimensions, Pressable, ActivityIndicator } from 'react-native';
import { useRouter } from 'expo-router';
import { useLoginViewModel } from '@/viewmodels/useLoginViewModel';

const LoginScreen = () => {
  const router = useRouter();
  // 1. Consome o hook para obter estado e funções
  const {
    email,
    setEmail,
    password,
    setPassword,
    isSubmitting, // Correção: Usando isSubmitting em vez de isLoading
    error,
    handleLogin,
  } = useLoginViewModel();

  return (
    <View style={styles.container}>
      <Image
        source={require('@/assets/images/saude_conn_logo.png')}
        style={styles.reactLogo}
        resizeMode="contain"
      />
      <Text style={styles.title}>Login</Text>

      {error && <Text style={styles.errorText}>{error}</Text>}

      <TextInput
        style={styles.input}
        placeholder="E-mail"
        value={email}
        onChangeText={setEmail}
        inputMode="email"
        autoCapitalize="none"
        readOnly={isSubmitting} // Correção: Usando isSubmitting
      />
      <TextInput
        style={styles.input}
        placeholder="Senha"
        value={password}
        secureTextEntry
        onChangeText={setPassword}
        readOnly={isSubmitting} // Correção: Usando isSubmitting
      />

      <Pressable style={styles.buttonContainer} onPress={handleLogin} disabled={isSubmitting}>
        {isSubmitting ? (
          <ActivityIndicator color="#fff" />
        ) : (
          <Text style={styles.buttonText}>Entrar</Text>
        )}
      </Pressable>

      <Pressable onPress={() => router.push('/(auth)/cadastro')}>
        <Text style={styles.signupText}>Não tem conta ainda? <Text style={styles.linkText}>Clique aqui</Text></Text>
      </Pressable>
    </View>
  );
};

const { width } = Dimensions.get('window');

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    paddingHorizontal: 16,
    backgroundColor: 'white',
  },
  title: {
    fontSize: 24,
    marginBottom: 16,
    textAlign: 'center',
  },
  input: {
    width: width * 0.8,
    height: 45,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 12,
    paddingHorizontal: 10,
    borderRadius: 5,
  },
  reactLogo: {
    width: 350,
    height: 200,
    marginBottom: 20,
  },
  buttonContainer: {
    width: width * 0.8,
    height: 50,
    backgroundColor: '#007BFF',
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 5,
    marginTop: 10,
  },
  buttonText: {
    color: 'white',
    fontSize: 18,
  },
  signupText: {
    marginTop: 20,
    fontSize: 16,
  },
  linkText: {
    color: '#007BFF',
    textDecorationLine: 'underline',
  },
  errorText: {
    color: 'red',
    marginBottom: 10,
    textAlign: 'center',
  }
});

export default LoginScreen;
