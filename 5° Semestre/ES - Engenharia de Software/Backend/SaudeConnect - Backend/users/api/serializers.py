from rest_framework import serializers
from users import models


# Create your models here.
class UserSerializer(serializers.ModelSerializer):

    class Meta:
        model = models.UserProfile
        fields = [
            'first_name', 'last_name', 'username', 'cpf', 'email', 'phone',
            'city', 'state', 'password'
        ]
        extra_kwargs = {
            'password': {
                'write_only': True
            },
            'cpf': {
                'required': True
            },
            'email': {
                'required': True
            },
            'first_name': {
                'required': True
            },
            'last_name': {
                'required': True
            },
        }

    def create(self, validated_data):
        user = models.UserProfile.objects.create_user(
            first_name=validated_data['first_name'],
            last_name=validated_data['last_name'],
            username=validated_data['username'],
            cpf=validated_data['cpf'],
            email=validated_data['email'],
            phone=validated_data.get('phone', ''),
            city=validated_data.get('city', ''),
            state=validated_data.get('state', ''),
            password=validated_data['password'])
        return user
