import sys
import os
import subprocess
import numpy as np
import pandas as pd
import glob
import math
from tqdm import tqdm
from collections import OrderedDict
import random
from PIL import Image
import torch
import torch.nn as nn

#Clone and import CNNWordReco repository
if ~os.path.isdir('CNNWordReco'):
    subprocess.call(['git', 'clone', 'https://github.com/saztorralba/CNNWordReco'])
if 'CNNWordReco' not in sys.path:
    sys.path.append('CNNWordReco')
from utils.cnn_func import train_model, validate_model
from models.SimpleCNN import SimpleCNN

def load_data(files, cv=False, dolabels=False, **kwargs):
    n_samples = len(files)
    dataset = torch.zeros((n_samples,kwargs['input_channels'],kwargs['ysize'],kwargs['xsize']),dtype=torch.uint8)
    labels = torch.zeros((n_samples),dtype=torch.uint8)
    for i in tqdm(range(len(files)),disable=(kwargs['verbose']<2)):
        img = Image.open(files[i])
        img = img.resize((kwargs['xsize'],kwargs['ysize']))
        img = np.transpose(np.asarray(img),[2,1,0])
        dataset[i] = torch.from_numpy(img)
        if dolabels:
            labels[i] = kwargs['vocab'][files[i].split('/')[-2]]
        
    if cv == False:
        return dataset, labels
    
    #Do random train/validation split
    idx = [i for i in range(n_samples)]
    random.shuffle(idx)
    trainset = dataset[idx[0:int(n_samples*(1-kwargs['cv_percentage']))]]
    trainlabels = labels[idx[0:int(n_samples*(1-kwargs['cv_percentage']))]]
    validset = dataset[idx[int(n_samples*(1-kwargs['cv_percentage'])):]]
    validlabels = labels[idx[int(n_samples*(1-kwargs['cv_percentage'])):]]
    return trainset, validset, trainlabels, validlabels
    
def evaluate_model(testset,model,**kwargs):
    testlen = testset.shape[0]
    predictions = np.zeros((testlen,))
    nbatches = math.ceil(testlen/kwargs['batch_size'])
    with torch.no_grad():
        model = model.eval()
        with tqdm(total=nbatches,disable=(kwargs['verbose']<2)) as pbar:
            for b in range(nbatches):
                #Obtain batch
                X = testset[b*kwargs['batch_size']:min(testlen,(b+1)*kwargs['batch_size'])].clone().float().to(kwargs['device'])
                #Propagate
                posteriors = model(X)
                #Accumulate confusion matrix
                estimated = torch.argmax(posteriors,dim=1)
                predictions[b*kwargs['batch_size']:min(testlen,(b+1)*kwargs['batch_size'])] = estimated.detach().cpu().numpy()
                pbar.set_description('Testing')
                pbar.update()
    return predictions

def show_matrix(test_pred,testlabels,**kwargs):
    conf_matrix = {l:{l2:sum(test_pred[np.where(testlabels==kwargs['vocab'][l])[0]]==kwargs['vocab'][l2]) for l2 in kwargs['vocab']} for l in kwargs['vocab']}
    words = list(kwargs['vocab'].keys())
    width = 1 + max([len(w) for w in words])
    out='|'+'|'.rjust(width)
    for w in words:
        out+=(w+'|').rjust(width)
    print(out)
    out='|'+''.join(['-' for i in range(width-1)])+'|'
    for w in words:
        out+=''.join(['-' for i in range(width-1)])+'|'
    print(out)
    for w in words:
        out='|'+(w+'|').rjust(width)
        for w2 in words:
            out+=('{0:d}|'.format(int(conf_matrix[w][w2]))).rjust(width)
        print(out)
    
#Arguments
args = {
    'cv_percentage': 0.1,
    'xsize': 64,
    'ysize': 64,
    'input_channels': 3,
    'num_blocks': 3,
    'channels': 64,
    'dropout': 0.0,
    'embedding_size': 128,
    'epochs': 10,
    'batch_size': 8,
    'learning_rate': 0.001,
    'seed': 1,
    'device': torch.device(('cuda:0' if torch.cuda.is_available() else 'cpu')),
    'verbose': 1,
    'augment': False,
}

#Initialise the random seeds
random.seed(args['seed'])
np.random.seed(args['seed'])
torch.manual_seed(args['seed'])
torch.cuda.manual_seed(args['seed'])
torch.backends.cudnn.deterministic = True

args['vocab'] = {f.split('/')[-1]:i for i,f in enumerate(np.sort(glob.glob('../input/avengers-face-recognition/cropped_images/*')))}
args['inv_vocab'] = {i:f.split('/')[-1] for i,f in enumerate(np.sort(glob.glob('../input/avengers-face-recognition/cropped_images/*')))}

files = {f:np.sort(glob.glob('../input/avengers-face-recognition/cropped_images/'+f+'/*.*')) for f in args['vocab']}
print('Face distribution: -> {0:s}'.format('; '.join(['{0:s}: {1:.2f}%'.format(f,100*len(files[f])/sum([len(files[ff]) for ff in files])) for f in files])))

trainset, validset, trainlabels, validlabels = load_data(np.sort(glob.glob('../input/avengers-face-recognition/cropped_images/*/*.*')),True,True,**args)
args['mean'] = torch.mean(trainset.float())
args['std'] = torch.std(trainset.float())

print('Training: {0:d} faces. Evaluation: {1:d} faces.'.format(trainset.shape[0],validset.shape[0]))

#Model, optimiser and criterion
model = SimpleCNN(**args).to(args['device'])
optimizer = torch.optim.Adam(model.parameters(),lr=args['learning_rate'])
criterion = nn.NLLLoss(reduction='mean').to(args['device'])
best_acc = 0.0
for ep in range(1,args['epochs']+1):
    #Do backpropgation and validation epochs
    loss = train_model(trainset,trainlabels,model,optimizer,criterion,**args)
    acc = validate_model(validset,validlabels,model,**args)
    print('Epoch {0:d} of {1:d}. Training loss: {2:.2f}, cross-validation accuracy: {3:.2f}%'.format(ep,args['epochs'],loss,acc))
    if acc > best_acc:
        best_acc = acc
        predictions = evaluate_model(validset,model,**args)

print('Best accuracy: {0:.2f}%'.format(best_acc))
print('Confusion matrix:')
show_matrix(predictions,validlabels,**args)
