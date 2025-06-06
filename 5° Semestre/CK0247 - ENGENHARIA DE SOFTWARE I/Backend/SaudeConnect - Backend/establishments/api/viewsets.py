from rest_framework import viewsets
from rest_framework import filters
from django_filters.rest_framework import DjangoFilterBackend
from rest_framework.authentication import TokenAuthentication
from rest_framework.decorators import action
from rest_framework.permissions import IsAuthenticated

from establishments.models import Establishment, Evaluation
from establishments.api.serializers import EstablishmentAllDataSerializer, EvaluationSerializer

from rest_framework.response import Response
from rest_framework import status

from establishments.utils import haversine


# Create your viewsets here.
class EstablishmentViewSet(viewsets.ModelViewSet):
    queryset = Establishment.objects.all()
    serializer_class = EstablishmentAllDataSerializer

    # GET /api/establishments/get_establishments_geo/
    @action(methods=['GET'],
            detail=False,
            permission_classes=[IsAuthenticated],
            authentication_classes=[TokenAuthentication])
    def get_establishments_geo(self, request):
        try:
            latitude = float(
                self.request.query_params.get('latitude', '').strip())
            longitude = float(
                self.request.query_params.get('longitude', '').strip())
            radius = float(self.request.query_params.get('radius', '').strip())
        except ValueError:
            return Response(
                {
                    'detail':
                    'Latitude, longitude e raio devem ser números válidos.'
                },
                status=status.HTTP_400_BAD_REQUEST)

        establishments = Establishment.objects.all()
        nearby_establishments = []

        for establishment in establishments:
            if establishment.latitude_estabelecimento_decimo_grau and establishment.longitude_estabelecimento_decimo_grau:
                distance = haversine(
                    latitude, longitude,
                    establishment.latitude_estabelecimento_decimo_grau,
                    establishment.longitude_estabelecimento_decimo_grau)
                if distance <= radius:
                    nearby_establishments.append(establishment)

        serializer = EstablishmentAllDataSerializer(nearby_establishments,
                                                    many=True)

        return Response(serializer.data, status=status.HTTP_200_OK)


class EvaluationViewSet(viewsets.ModelViewSet):
    queryset = Evaluation.objects.all()
    serializer_class = EvaluationSerializer
    filter_backends = [DjangoFilterBackend, filters.OrderingFilter]
    ordering_fields = ['id', 'nota']
    ordering = ['id']
    permission_classes = [IsAuthenticated]
    authentication_classes = [TokenAuthentication]

    def get_queryset(self):
        """
        Optionally restricts the returned evaluations to a given establishment or user,
        by filtering against a `estabelecimento` or `usuario_avaliador` query parameter.
        """
        queryset = Evaluation.objects.all()
        estabelecimento = self.request.query_params.get(
            'estabelecimento', None)
        usuario_avaliador = self.request.query_params.get(
            'usuario_avaliador', None)
        if estabelecimento:
            queryset = queryset.filter(estabelecimento=estabelecimento)
        if usuario_avaliador:
            queryset = queryset.filter(usuario_avaliador=usuario_avaliador)
        return queryset
