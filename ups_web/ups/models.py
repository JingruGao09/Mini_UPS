from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.conf import settings
from django.dispatch import receiver
import uuid

class Profile(models.Model):
    #amazon pass the user id to ups when the purchase was made
    userId = models.IntegerField(primary_key=True)
    #id = models.UUIDField(primary_key=True, default=uuid.uuid4)
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
