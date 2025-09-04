from django.contrib import admin
from django.contrib.auth.models import User
from django.contrib.auth.admin import UserAdmin as DjangoUserAdmin
from users.models import UserProfile, SolicitationNewPassword


# Register your models here.
@admin.register(User)
class UserAdmin(DjangoUserAdmin):
    fieldsets = (
        (None, {
            'fields': ('first_name', 'last_name', 'username', 'password',
                       'email', 'cpf', 'phone')
        }),
        ('Localização', {
            'fields': (
                'state',
                'city',
            )
        }),
        ('Permissões', {
            'fields': ('is_active', 'is_staff', 'is_superuser', 'groups',
                       'user_permissions')
        }),
        ('Datas importantes', {
            'fields': ('last_login', 'date_joined')
        }),
    )
    add_fieldsets = ((None, {
        'classes': ('wide', ),
        'fields': ('username', 'email', 'password1', 'password2'),
    }), )
    filter_horizontal = ['groups', 'user_permissions']
    list_display = ['id', 'email', 'first_name', 'last_name', 'is_staff']
    search_fields = ['email', 'first_name', 'last_name']
    ordering = [
        'email',
    ]


# @admin.register(SolicitationNewPassword)
class SolicitationNewPasswordAdmin(admin.ModelAdmin):
    fieldsets = (
        ('Dados solicitante', {
            'fields': ('user_request', )
        }),
        ('Dados solicitação', {
            'fields': ('recovery_code', 'date_request', 'action_completed')
        }),
    )

    list_display = ['id', 'user_request', 'date_request', 'action_completed']
    search_fields = [
        'user_request__email',
    ]
    list_filter = [
        'action_completed',
    ]

    def get_readonly_fields(self, request, obj=None):
        return self.readonly_fields + ('user_request', 'recovery_code',
                                       'date_request', 'action_completed')


admin.site.site_header = "Painel Administrativo Saúde Connect"
admin.site.site_title = "SaudeConnect"

admin.site.register(UserProfile, UserAdmin)
# admin.site.register(SolicitationNewPasswordAdmin, SolicitationNewPassword)
