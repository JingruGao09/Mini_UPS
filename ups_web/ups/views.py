from django.shortcuts import render
from django.http import HttpResponse
from django.db.models import Q

def index(request):
    return HttpResponse("Hello, world. You're at the UPS index.")

def home(request):
    #return render(request, 'home.html')
    return render(request, 'base_generic.html')

def SearchRideView(request):
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
