from rest_framework.permissions import BasePermission


class OwnUserPermission(BasePermission):
    def has_permission(self, request, view):
        return not view.kwargs.get('pk') or request.user.id == int(view.kwargs['pk'])
