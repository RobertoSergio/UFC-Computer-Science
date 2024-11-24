from django.db import models
from django.contrib.auth.base_user import BaseUserManager
from django.contrib.auth.models import AbstractUser
from rest_framework.authtoken.models import Token
from django.contrib.auth.models import User
from datetime import datetime


# Create your models here.
class UserManager(BaseUserManager):
    use_in_migrations = True

    def _create_user(self, email, password, **extra_fields):
        if not email:
            raise ValueError('The given email must be set')
        email = self.normalize_email(email)
        user = self.model(email=email, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_user(self, email, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', False)
        extra_fields.setdefault('is_superuser', False)
        return self._create_user(email, password, **extra_fields)

    def create_superuser(self, email, password, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        if extra_fields.get('is_staff') is not True:
            raise ValueError('Superuser must have is_staff=True.')
        if extra_fields.get('is_superuser') is not True:
            raise ValueError('Superuser must have is_superuser=True.')

        return self._create_user(email, password, **extra_fields)


class UserProfile(AbstractUser):
    email = models.EmailField(unique=True, null=True, blank=True)
    # photo = models.ImageField(upload_to='usuarioimagens/', default='pic_folder/guest_user.jpg', blank=True, null=True)
    photo_url = models.URLField(
        default="",
        blank=True
    )
    is_staff = models.BooleanField('Membros da Equipe', default=False, help_text=u"Somente membros da equipe tem acesso ao site administrativo.")
    cpf = models.CharField(u'CPF', max_length=14, blank=True, null=True)
    phone = models.CharField('Telefone/Celular', max_length=20, blank=True, null=True)
    state = models.CharField('Estado', max_length=124, default="", blank=True)
    city = models.CharField('Cidade', max_length=124, default="", blank=True)

    objects = UserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['username']

    def __str__(self):
        return self.email

    class Meta:
        verbose_name = u'usuário'
        verbose_name_plural = u'Usuários'

    def save(self, *args, **kwargs):
        super(UserProfile, self).save(*args, **kwargs)


class SolicitationNewPassword(models.Model):
    user_request = models.ForeignKey(UserProfile, verbose_name=u'Usuário solicitante', on_delete=models.CASCADE, null=False)
    recovery_code = models.CharField(u'Código de recuperação', max_length=10, null=False, blank=False, unique=True)
    date_request = models.DateTimeField(u'Data da solicitação', default=datetime.now)
    action_completed = models.BooleanField(u'Solicitação finalizada ?', default=False)

    def __str__(self):
        return str(self.id)

    class Meta:
        verbose_name = u'solicitação'
        verbose_name_plural = u'Solicitações'
