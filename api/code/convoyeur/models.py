import uuid
from django.db import models

class Package(models.Model):
    DESTINATIONS = {
        ("Right", "Right"),
        ("Straight", "Straight"),
        ("Left", "Left")
    }

    uuid = models.CharField(max_length=30, unique=True)
    destination = models.CharField(max_length=10, choices=DESTINATIONS)
    delivered = models.BooleanField(default=False)
    scanned = models.BooleanField(default=False)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

class AlarmCustom(models.Model):

    message = models.TextField()
    active = models.SmallIntegerField(default=1)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
