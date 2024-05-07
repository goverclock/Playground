#!env python3

def make_car(builder, model, **kwargs):
    kwargs['builder'] = builder
    kwargs['model'] = model
    return kwargs

#print(make_car('me', 'random', color='blue', tow_package=True))

