// gen/src/repositories/userRepository.ts

import { User } from '@/types/User';
import AsyncStorage from '@react-native-async-storage/async-storage';

// Mapeamento das chaves para evitar erros de digitação
const userKeys = {
  TOKEN: 'userToken',
  ID: 'userId',
  FIRST_NAME: 'userFirstname',
  LAST_NAME: 'userLastname',
  PHONE: 'userPhone',
  EMAIL: 'userEmail',
  CPF: 'userCPF',
  USERNAME: 'userUsername',
  PHOTO_URL: 'userPhotoUrl',
  DATE_JOINED: 'userDateJoined',
  CITY: 'userCity',
  STATE: 'userState',
};

export const userRepository = {
  saveUserData: async (data: User): Promise<void> => {
    try {
      const userDataPairs: [string, string][] = [
        [userKeys.TOKEN, data.token],
        [userKeys.ID, data.id],
        [userKeys.FIRST_NAME, data.first_name],
        [userKeys.LAST_NAME, data.last_name],
        [userKeys.PHONE, data.telefone || ''],
        [userKeys.EMAIL, data.email],
        [userKeys.CPF, data.cpf],
        [userKeys.USERNAME, data.username],
        [userKeys.PHOTO_URL, data.photo_url || ''],
        [userKeys.DATE_JOINED, data.data_joined],
        [userKeys.CITY, data.city],
        [userKeys.STATE, data.state],
      ];
      await AsyncStorage.multiSet(userDataPairs);
    } catch (error) {
      console.error('Erro ao salvar os dados do usuário:', error);
      throw new Error('Não foi possível salvar os dados do usuário.');
    }
  },

  getUserData: async (): Promise<Partial<User>> => {
    try {
        const keys = Object.values(userKeys);
        const storedData = await AsyncStorage.multiGet(keys);
        const userData: Partial<User> = {};
        
        storedData.forEach(([key, value]) => {
            const userKey = Object.keys(userKeys).find(k => userKeys[k as keyof typeof userKeys] === key) as keyof User;
            if (userKey) {
                (userData as any)[userKey.toLowerCase()] = value;
            }
        });

        return userData;
    } catch (error) {
        console.error('Erro ao carregar dados do usuário:', error);
        return {};
    }
  },

  getUserId: (): Promise<string | null> => {
    return AsyncStorage.getItem(userKeys.ID);
  },
  
  clearUserData: async (): Promise<void> => {
    try {
      const keys = Object.values(userKeys);
      await AsyncStorage.multiRemove(keys);
    } catch (error) {
      console.error('Erro ao limpar dados do usuário:', error);
      throw new Error('Não foi possível realizar o logout.');
    }
  },
};