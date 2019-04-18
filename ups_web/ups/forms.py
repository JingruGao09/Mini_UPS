from django import forms
from .models import UpsProfile
from django.shortcuts import render
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
class CustomUserCreationForm(UserCreationForm):
    email = forms.EmailField(label='Enter email',required=True)

    class Meta:
        model = User
        fields = ('username', 'email', 'password1', 'password2', )
    '''
    def save(self, commit=True):
    user = UpsProfile.objects.create_user(
    self.cleaned_data['username'],
    self.cleaned_data['email'],
    self.cleaned_data['password1']
    )
    return user
    '''
class PackageMatchForm(forms.Form):
    package_id = forms.IntegerField(label = 'Your Package ID',required = True)

class EditPackageDestForm(forms.Form):
    des_x = forms.IntegerField(label = 'delivery dest x',required = True)
    des_y = forms.IntegerField(label = 'delivery dest y',required = True)
