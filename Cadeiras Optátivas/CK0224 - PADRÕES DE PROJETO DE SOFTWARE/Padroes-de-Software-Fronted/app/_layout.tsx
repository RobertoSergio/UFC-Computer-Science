// gen/app/_layout.tsx

import { useEffect } from 'react';
import { useFonts } from 'expo-font';
import { Stack, useRouter, useSegments } from 'expo-router';
import * as SplashScreen from 'expo-splash-screen';
import 'react-native-reanimated';
import { DependencyProvider } from '@/contexts/DependencyContext';
import { useAuthStore } from '@/stores/useAuthStore';
import { ThemeProvider, DarkTheme, DefaultTheme } from '@react-navigation/native';
import { useColorScheme } from '@/hooks/useColorScheme';

SplashScreen.preventAutoHideAsync();

const AppLayout = () => {
    const { isAuthenticated, isLoading, loadUserFromStorage } = useAuthStore();
    const segments = useSegments();
    const router = useRouter();
    const colorScheme = useColorScheme();
    const [loaded] = useFonts({
        SpaceMono: require('../src/assets/fonts/SpaceMono-Regular.ttf'),
      });

    useEffect(() => {
        // Verifica o storage uma vez quando o app carrega
        loadUserFromStorage();
    }, []);

    useEffect(() => {
        if (!loaded || isLoading) return; // Espera a store e as fontes carregarem

        const inAuthGroup = segments[0] === '(auth)';

        if (isAuthenticated && inAuthGroup) {
            // Se o usuário está autenticado e na tela de login, redireciona para a home
            router.replace('/(tabs)/home');
        } else if (!isAuthenticated && !inAuthGroup) {
            // Se não está autenticado e fora do grupo de auth, redireciona para o login
            router.replace('/(auth)');
        }
        SplashScreen.hideAsync();
    }, [isAuthenticated, isLoading, segments, loaded]);

    if (!loaded || isLoading) {
        return null; // ou uma tela de splash
    }

    return (
        <ThemeProvider value={colorScheme === 'dark' ? DarkTheme : DefaultTheme}>
            <Stack>
                <Stack.Screen name="+not-found" />
            </Stack>
        </ThemeProvider>
    );
};


export default function RootLayout() {
  return (
    <DependencyProvider>
        <AppLayout/>
    </DependencyProvider>
  );
}