# Generated by Django 3.2.17 on 2023-02-08 19:48

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('convoyeur', '0015_alter_package_destination'),
    ]

    operations = [
        migrations.AlterField(
            model_name='package',
            name='destination',
            field=models.CharField(choices=[('Straight', 'Straight'), ('Left', 'Left'), ('Right', 'Right')], max_length=10),
        ),
    ]