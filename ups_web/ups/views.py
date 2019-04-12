from django.shortcuts import render,redirect, get_object_or_404
from django.http import HttpResponse
from django.db.models import Q
from ups.models import Package
from django.template import loader
from django.contrib.auth.forms import UserCreationForm
from .forms import CustomUserCreationForm
from django.contrib.auth import login, authenticate
def index(request):
    return HttpResponse("Hello, world. You're at the UPS index.")

def home(request):
    return render(request, 'base_generic.html')

def TrackPackageView(request):
    error = False
    if 'TrackingNumber'in request.GET:
        tracknum = request.GET['TrackingNumber']
        if not tracknum:
            error = True
        else:
            package_list = Package.objects.filter(package_id = tracknum)
            template = loader.get_template('ups/package_list.html')
            context = {
                'package_list' : package_list,
            }
            return HttpResponse(template.render(context, request))
    return render(request, 'ups/trackPackage.html')

def RegisterUserView(request):
    form = CustomUserCreationForm(request.POST)
    if request.method == 'POST':
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            username = form.cleaned_data.get('username')
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=username, password=raw_password)
            login(request, user)
            '''                                
            new_username = form.cleaned_data['username'].lower()
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=username, password=raw_password)
            messages.success(request, 'Account created successfully')
            login(request, user)        
            '''
            return render(request, 'base_generic.html')
    else:
        form = CustomUserCreationForm()            
    return render(request, 'ups/registerUser.html', {'form': form})
    

