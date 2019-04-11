from django import forms
from .models import Profile
from django.shortcuts import render

def home(request):
    return render(request, 'home.html')
