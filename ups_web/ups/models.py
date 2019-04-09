from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.conf import settings
import uuid
from uuid import uuid4
from django.dispatch import receiver

class Profile(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text="Unique ID for this user")
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='profile')
    def __str__(self):
        """String for representing the Model object (in Admin site etc.)"""
        return self.user.__str__()

@receiver(post_save, sender=User)
def create_user_profile(sender, instance, created, **kwargs):
    if created:
        Prof.objects.create(user=instance)

@receiver(post_save, sender=User)
def save_user_profile(sender, instance, **kwargs):
    post_save.disconnect(save_user_profile, sender=User)
    instance.profile.save()
    post_save.connect(save_user_profile, sender=User)
