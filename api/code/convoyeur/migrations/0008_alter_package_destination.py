# Generated by Django 3.2.17 on 2023-02-05 17:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('convoyeur', '0007_alter_package_destination'),
    ]

    operations = [
        migrations.AlterField(
            model_name='package',
            name='destination',
            field=models.CharField(choices=[('Left', 'Left'), ('Straight', 'Straight'), ('Right', 'Right')], max_length=10),
        ),
    ]
