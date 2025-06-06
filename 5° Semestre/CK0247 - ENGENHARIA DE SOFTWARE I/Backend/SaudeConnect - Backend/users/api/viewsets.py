from rest_framework import viewsets
from rest_framework.decorators import action
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework import status
from rest_framework.authtoken.models import Token

from .serializers import UserSerializer
from users.models import UserProfile, SolicitationNewPassword

from django.contrib.auth import authenticate
import random
import string


# Create your viewsets here.
class UserViewset(viewsets.ModelViewSet):
    queryset = UserProfile.objects.all()
    serializer_class = UserSerializer

    @action(methods=['POST'], detail=False, permission_classes=[AllowAny])
    def authentication(self, request):
        email = request.data.get('email')
        password = request.data.get('password')
        user = authenticate(email=email, password=password)

        if user:
            token, created = Token.objects.get_or_create(user=user)

            payload_user = {
                'id': user.id,
                'token': token.key,
                'first_name': user.first_name,
                'last_name': user.last_name,
                'username': user.username,
                'cpf': user.cpf,
                'email': user.email,
                'phone': user.phone,
                'photo_url': user.photo_url,
                'data_joined': user.date_joined,
                'city': user.city,
                'state': user.state
            }

            return Response(payload_user, status=status.HTTP_200_OK)
        else:
            return Response({'error': 'Credenciais inválidas'},
                            status=status.HTTP_400_BAD_REQUEST)

    def post(self, request):
        serializer = UserSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
