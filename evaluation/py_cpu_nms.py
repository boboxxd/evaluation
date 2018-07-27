import numpy as np

# cls_idx, score, bbox_x1, bbox_y1, bbox_x2, bbox_y2
def nms(dets, thresh=0.3):
    results = []
    scores = np.asarray([det[1] for det in dets])
    x1     = np.asarray([det[2] for det in dets])
    y1     = np.asarray([det[3] for det in dets])
    x2     = np.asarray([det[4] for det in dets])
    y2     = np.asarray([det[5] for det in dets])
    areas  = (x2 - x1 + 1) * (y2 - y1 + 1)
    order  = scores.argsort()[::-1]
    keep = []
    while order.size > 0:
        i = order[0]
        keep.append(i)
        xx1 = np.maximum(x1[i], x1[order[1:]])
        yy1 = np.maximum(y1[i], y1[order[1:]])
        xx2 = np.minimum(x2[i], x2[order[1:]])
        yy2 = np.minimum(y2[i], y2[order[1:]])

        w = np.maximum(0.0, xx2 - xx1 + 1)
        h = np.maximum(0.0, yy2 - yy1 + 1)
        inter = w * h
        ovr = inter / (areas[i] + areas[order[1:]] - inter)

        inds = np.where(ovr <= thresh)[0]
        order = order[inds + 1]

    for index in keep:
        results.append(dets[index])

    return results

