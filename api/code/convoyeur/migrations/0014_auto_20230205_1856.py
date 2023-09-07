# Generated by Django 3.2.17 on 2023-02-05 18:56

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('convoyeur', '0013_auto_20230205_1854'),
    ]

    operations = [
        migrations.AddField(
            model_name='package',
            name='created_at',
            field=models.DateTimeField(auto_now_add=True, default='2000-01-01 00:00'),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='package',
            name='delivered',
            field=models.BooleanField(default=False),
        ),
        migrations.AddField(
            model_name='package',
            name='scanned',
            field=models.BooleanField(default=False),
        ),
        migrations.AddField(
            model_name='package',
            name='updated_at',
            field=models.DateTimeField(auto_now=True),
        ),
        migrations.AlterField(
            model_name='package',
            name='destination',
            field=models.CharField(choices=[('Straight', 'Straight'), ('Right', 'Right'), ('Left', 'Left')], max_length=10),
        ),
    ]
