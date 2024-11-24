from django.contrib import admin
from .models import Establishment, Evaluation


# Register your models here.
class EstablishmentAdmin(admin.ModelAdmin):
    list_display = [
        'id', 'codigo_cnes', 'nome_fantasia', 'endereco_estabelecimento',
        'bairro_estabelecimento', 'numero_telefone_estabelecimento',
        'latitude_estabelecimento_decimo_grau',
        'longitude_estabelecimento_decimo_grau'
    ]
    search_fields = [
        'codigo_cnes', 'numero_cnpj_entidade', 'nome_razao_social',
        'nome_fantasia', 'codigo_estabelecimento_saude'
    ]
    list_filter = [
        'tipo_gestao', 'estabelecimento_faz_atendimento_ambulatorial_sus',
        'estabelecimento_possui_centro_cirurgico',
        'estabelecimento_possui_centro_obstetrico',
        'estabelecimento_possui_centro_neonatal',
        'estabelecimento_possui_atendimento_hospitalar',
        'estabelecimento_possui_servico_apoio',
        'estabelecimento_possui_atendimento_ambulatorial'
    ]

    def get_readonly_fields(self, request, obj=None):
        return self.readonly_fields + (
            'codigo_cnes', 'numero_cnpj_entidade', 'nome_razao_social',
            'nome_fantasia', 'natureza_organizacao_entidade', 'tipo_gestao',
            'descricao_nivel_hierarquia', 'descricao_esfera_administrativa',
            'codigo_tipo_unidade', 'codigo_cep_estabelecimento',
            'endereco_estabelecimento', 'numero_estabelecimento',
            'bairro_estabelecimento', 'numero_telefone_estabelecimento',
            'latitude_estabelecimento_decimo_grau',
            'longitude_estabelecimento_decimo_grau',
            'endereco_email_estabelecimento', 'numero_cnpj',
            'codigo_identificador_turno_atendimento',
            'descricao_turno_atendimento',
            'estabelecimento_faz_atendimento_ambulatorial_sus',
            'codigo_estabelecimento_saude', 'codigo_uf', 'codigo_municipio',
            'descricao_natureza_juridica_estabelecimento',
            'codigo_motivo_desabilitacao_estabelecimento',
            'estabelecimento_possui_centro_cirurgico',
            'estabelecimento_possui_centro_obstetrico',
            'estabelecimento_possui_centro_neonatal',
            'estabelecimento_possui_atendimento_hospitalar',
            'estabelecimento_possui_servico_apoio',
            'estabelecimento_possui_atendimento_ambulatorial',
            'codigo_atividade_ensino_unidade',
            'codigo_natureza_organizacao_unidade',
            'codigo_nivel_hierarquia_unidade',
            'codigo_esfera_administrativa_unidade')


class EvaluationAdmin(admin.ModelAdmin):
    list_display = [
        'estabelecimento', 'usuario_avaliador', 'nota', 'descricao'
    ]
    list_filter = ['estabelecimento', 'nota']
    search_fields = [
        'estabelecimento__nome_fantasia', 'usuario_avaliador__username'
    ]

    def get_readonly_fields(self, request, obj=None):
        if not request.user.is_superuser:  # Opcional: permite que superusuários editem
            return [field.name for field in self.model._meta.get_fields()]
        return super().get_readonly_fields(request, obj)

    def has_change_permission(self, request, obj=None):
        return False

    def has_delete_permission(self, request, obj=None):
        return False

    def has_add_permission(self, request):
        return False


admin.site.register(Establishment, EstablishmentAdmin)
admin.site.register(Evaluation, EvaluationAdmin)
