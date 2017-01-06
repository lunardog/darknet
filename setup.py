from distutils.core import setup, Extension
import os

objects = ['obj/{}'.format(obj) for obj in ['gemm.o', 'utils.o', 'cuda.o', 'convolutional_layer.o', 'list.o', 'image.o', 'activations.o', 'im2col.o', 'col2im.o', 'blas.o', 'crop_layer.o', 'dropout_layer.o', 'maxpool_layer.o', 'softmax_layer.o', 'data.o', 'matrix.o', 'network.o', 'connected_layer.o', 'cost_layer.o', 'parser.o', 'option_list.o', 'darknet.o', 'detection_layer.o', 'captcha.o', 'route_layer.o', 'writing.o', 'box.o', 'nightmare.o', 'normalization_layer.o', 'avgpool_layer.o', 'coco.o', 'dice.o', 'yolo.o', 'detector.o', 'layer.o', 'compare.o', 'classifier.o', 'local_layer.o', 'swag.o', 'shortcut_layer.o', 'activation_layer.o', 'rnn_layer.o', 'gru_layer.o', 'rnn.o', 'rnn_vid.o', 'crnn_layer.o', 'demo.o', 'tag.o', 'cifar.o', 'go.o', 'batchnorm_layer.o', 'art.o', 'region_layer.o', 'reorg_layer.o', 'super.o', 'voxel.o', 'tree.o']]

py_darknet = Extension('darknet', 
    sources=['src/py_darknet.c'],
    extra_objects=objects
)

setup (name = 'DarkNet Python',
    version = '1.0',
    description = 'Python binding for darknet',
    ext_modules = [py_darknet],
    # extra_objects=objects
)
