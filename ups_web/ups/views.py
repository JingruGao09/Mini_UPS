from django.shortcuts import render,redirect, get_object_or_404
from django.conf import settings
from django.http import HttpResponse
from django.db.models import Q
from ups.models import Package
from django.template import loader
from django.contrib.auth.forms import UserCreationForm
from .forms import CustomUserCreationForm
from django.contrib.auth import login, authenticate
from .models import UpsProfile,Truck,Package,Shipment

import pdb

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
            return render(request, 'base_generic.html')
    else:
        form = CustomUserCreationForm()            
    return render(request, 'ups/registerUser.html', {'form': form})

from django.views import generic
from django.contrib.auth.decorators import login_required
from django.utils.decorators import method_decorator


def MyPackagesView(request):
    package_list = UpsProfile.objects.filter(user_id = request.user.pk).first().user_set.all()
    print(request.user.pk)
    #pdb.set_trace()

    print(package_list)
    #package_list = UpsProfile.objects.filter(pk = request.user.pk).first().package_set.all()
    #template = loader.get_template('ups/package_list.html')
    return render(request,'ups/myPackage_list.html',{'package_list':package_list})

@method_decorator(login_required, name='dispatch')
class PackageListView(generic.ListView):
    model = Package
    def get_queryset(self):
        return Package.objects.all()
    
@method_decorator(login_required, name='dispatch')
class PackageDetailView(generic.DetailView):
    model = Package

