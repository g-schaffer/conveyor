import json
from django.shortcuts import render
from rest_framework.views import APIView
from rest_framework.response import Response
from convoyeur.models import *
from django.core import serializers


class Destination(APIView):

    def get(self, request, format=None):

        packageUUID = request.GET.get("uuid", "")

        package = Package.objects.get(uuid= packageUUID)
        package.scanned = True
        package.delivered = False
        package.save()

        return Response(package.destination)

class Delivered(APIView):

    def post(self, request, format=None):

        packageUUID = request.body.decode('utf-8')

        # Check delivered package
        package = Package.objects.get(uuid= packageUUID)
        package.delivered = True
        package.scanned = False
        package.save()

        return Response("ok")

class OnDelivery(APIView):

    def get(self, request, format=None):
        
        # Get all package scanned but not delivered (onDelivery)
        count = Package.objects.filter(scanned=True, delivered=False).count()

        return Response(count)

class CleanOnDelivery(APIView):

    def post(self, request, format=None):
        
        # Get all package scanned but not delivered (onDelivery)
        listPackage = list(Package.objects.filter(scanned=True, delivered=False))

        # Reset all package onDelivery
        for p in listPackage:
            p.scanned = False
            p.delivered = False
            p.save()

        return Response(len(listPackage))

class ResetAllPackages(APIView):

    def get(self, request, format=None):

        packaged = Package.objects.all()

        for package in packaged:
            package.delivered = False
            package.scanned = False
            package.save()

        return Response("ok")

class Alarm(APIView):

    def post(self, request, format=None):

        msg = request.body.decode('utf-8')

        nbAlarmsActive = AlarmCustom.objects.filter(message=msg, active=1).count()

        if(nbAlarmsActive == 0):
            AlarmCustom.objects.create(message=msg)

        return Response("ok")

class ResetAlarm(APIView):

    def post(self, request, format=None):

        alarm = AlarmCustom.objects.last()

        alarm.active = 0
        alarm.save()

        return Response("ok")

