"""project URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.conf.urls import include

from convoyeur.views import Destination, OnDelivery, Delivered, ResetAllPackages, Alarm, ResetAlarm, CleanOnDelivery

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api-auth/', include('rest_framework.urls')),

    path('destination', Destination.as_view()),
    
    path('delivered', Delivered.as_view()),

    path('onDelivery', OnDelivery.as_view()),

    path('onDelivery/clean', CleanOnDelivery.as_view()),

    path('resetAllPackages', ResetAllPackages.as_view()),

    path('alarm', Alarm.as_view()),

    path('resetAlarm', ResetAlarm.as_view()),

]
