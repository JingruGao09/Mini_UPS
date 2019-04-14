from django.urls import path
from . import views
from django.contrib.auth import views as auth_views
urlpatterns = [
    path('', views.home, name='home'),
    path('trackPackage/',views.TrackPackageView,name='TrackPackageView'),
    path('registerUser/', views.RegisterUserView, name='RegisterUserView'),
    path('login/',auth_views.LoginView.as_view(template_name='ups/login.html'), name='login'),
    path('logout/',auth_views.LogoutView.as_view(), name='logout'),
    path('myPackages/',views.MyPackagesView,name='myPackages'),
]
