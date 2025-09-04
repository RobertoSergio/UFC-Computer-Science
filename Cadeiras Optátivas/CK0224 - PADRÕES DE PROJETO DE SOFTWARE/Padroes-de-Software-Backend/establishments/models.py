from django.db import models
from django.core.exceptions import ValidationError

from users.models import UserProfile


# Create your models here.
def validate_range(value):
    if not (0 <= value <= 5):
        raise ValidationError('O valor deve estar entre 0 e 5.')


class Establishment(models.Model):
    codigo_cnes = models.BigIntegerField(verbose_name="Código CNES")
    numero_cnpj_entidade = models.CharField(
        max_length=14, verbose_name="Número CNPJ da Entidade")
    nome_razao_social = models.CharField(max_length=255,
                                         verbose_name="Nome/Razão Social")
    nome_fantasia = models.CharField(max_length=255,
                                     verbose_name="Nome Fantasia")
    natureza_organizacao_entidade = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Natureza da Organização da Entidade")
    tipo_gestao = models.CharField(max_length=1, verbose_name="Tipo de Gestão")
    descricao_nivel_hierarquia = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Descrição do Nível Hierárquico")
    descricao_esfera_administrativa = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Descrição da Esfera Administrativa")
    codigo_tipo_unidade = models.IntegerField(
        verbose_name="Código Tipo de Unidade")
    codigo_cep_estabelecimento = models.CharField(
        max_length=8, verbose_name="Código CEP do Estabelecimento")
    endereco_estabelecimento = models.CharField(
        max_length=255, verbose_name="Endereço do Estabelecimento")
    numero_estabelecimento = models.CharField(
        max_length=10, verbose_name="Número do Estabelecimento")
    bairro_estabelecimento = models.CharField(
        max_length=255, verbose_name="Bairro do Estabelecimento")
    numero_telefone_estabelecimento = models.CharField(
        max_length=15,
        null=True,
        blank=True,
        verbose_name="Número de Telefone do Estabelecimento")
    latitude_estabelecimento_decimo_grau = models.FloatField(
        null=True,
        blank=True,
        verbose_name="Latitude do Estabelecimento (Decimos de Grau)")
    longitude_estabelecimento_decimo_grau = models.FloatField(
        null=True,
        blank=True,
        verbose_name="Longitude do Estabelecimento (Decimos de Grau)")
    endereco_email_estabelecimento = models.EmailField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Endereço de E-mail do Estabelecimento")
    numero_cnpj = models.CharField(max_length=14,
                                   null=True,
                                   blank=True,
                                   verbose_name="Número CNPJ")
    codigo_identificador_turno_atendimento = models.CharField(
        max_length=2,
        verbose_name="Código Identificador do Turno de Atendimento")
    descricao_turno_atendimento = models.CharField(
        max_length=255, verbose_name="Descrição do Turno de Atendimento")
    estabelecimento_faz_atendimento_ambulatorial_sus = models.CharField(
        max_length=3,
        verbose_name="Estabelecimento Faz Atendimento Ambulatorial SUS")
    codigo_estabelecimento_saude = models.CharField(
        max_length=14, verbose_name="Código do Estabelecimento de Saúde")
    codigo_uf = models.IntegerField(verbose_name="Código UF")
    codigo_municipio = models.IntegerField(verbose_name="Código Município")
    descricao_natureza_juridica_estabelecimento = models.CharField(
        max_length=4,
        verbose_name="Descrição da Natureza Jurídica do Estabelecimento")
    codigo_motivo_desabilitacao_estabelecimento = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Código Motivo Desabilitação do Estabelecimento")
    estabelecimento_possui_centro_cirurgico = models.BooleanField(
        default=False,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Centro Cirúrgico")
    estabelecimento_possui_centro_obstetrico = models.BooleanField(
        default=False,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Centro Obstétrico")
    estabelecimento_possui_centro_neonatal = models.BooleanField(
        default=False,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Centro Neonatal")
    estabelecimento_possui_atendimento_hospitalar = models.BooleanField(
        default=False,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Atendimento Hospitalar")
    estabelecimento_possui_servico_apoio = models.BooleanField(
        default=True,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Serviço de Apoio")
    estabelecimento_possui_atendimento_ambulatorial = models.BooleanField(
        default=False,
        null=True,
        blank=True,
        verbose_name="Estabelecimento Possui Atendimento Ambulatorial")
    codigo_atividade_ensino_unidade = models.CharField(
        max_length=2, verbose_name="Código Atividade Ensino Unidade")
    codigo_natureza_organizacao_unidade = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Código Natureza Organização Unidade")
    codigo_nivel_hierarquia_unidade = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Código Nível Hierárquico Unidade")
    codigo_esfera_administrativa_unidade = models.CharField(
        max_length=255,
        null=True,
        blank=True,
        verbose_name="Código Esfera Administrativa Unidade")

    def __str__(self):
        return str(f"{self.codigo_cnes} - {self.nome_fantasia}")

    class Meta:
        verbose_name = u'estabelecimento'
        verbose_name_plural = u'Estabelecimentos'


class Evaluation(models.Model):
    estabelecimento = models.ForeignKey(
        Establishment,
        verbose_name="Estabelecimento avaliado",
        on_delete=models.CASCADE)
    usuario_avaliador = models.ForeignKey(UserProfile,
                                          verbose_name="Usuário avaliador",
                                          on_delete=models.CASCADE)
    nota = models.PositiveIntegerField(validators=[validate_range])
    descricao = models.TextField(max_length=500, null=True, blank=True)

    def __str__(self):
        return str(f"{self.estabelecimento} - {self.usuario_avaliador}")

    class Meta:
        verbose_name = u'Avaliação'
        verbose_name_plural = u'Avaliações'
        constraints = [
            models.UniqueConstraint(
                fields=['estabelecimento', 'usuario_avaliador'],
                name='unique_evaluation')
        ]
