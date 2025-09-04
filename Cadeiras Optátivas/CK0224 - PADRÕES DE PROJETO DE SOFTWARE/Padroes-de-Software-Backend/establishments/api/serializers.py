from rest_framework import serializers
from establishments.models import Establishment, Evaluation


# Create your serializers here.
class EstablishmentAllDataSerializer(serializers.ModelSerializer):

    class Meta:
        model = Establishment
        fields = "__all__"


class EvaluationSerializer(serializers.ModelSerializer):

    class Meta:
        model = Evaluation
        fields = [
            'id', 'estabelecimento', 'usuario_avaliador', 'nota', 'descricao'
        ]
