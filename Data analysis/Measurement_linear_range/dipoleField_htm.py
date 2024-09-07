import numpy as np

mu0 = 4e-7 * np.pi # vacuum magnetic permeability in Newtons / Amps ^ 2
muR_air = 1. # relative permeability of air

def electromagneticCoilMomentMagnitude(numCoilLoops: int, wireCrossSectionArea: float, coilAmps: float):
    # numCoilLoops = number of coil loops/turns in the electromagnet
    # wireCrossSectionArea = cross-sectional area of the wire in Meters^2
    # coilAmps = current flowing through the coil in Amperes
    # returns: magnetic moment magnitude of the electromagnetic coil in Amps * Meters^2
    return numCoilLoops * wireCrossSectionArea * coilAmps

def dipoleMagneticFluxDensity_htm(momentMagnitude: float, htm_originToDipoleCenter: np.ndarray, htm_originToMeasurementPoint: np.ndarray):
    # momentMagnitude = dipole moment magnitude in Amps * Meters ^ 2
    # htm_originToDipoleCenter = 4x4 homogeneous transformation matrix from some origin to the dipole center (distances in Meters)
    # htm_originToMeasurementPoint = 4x4 homogeneous transformation matrix from some origin to the measurement point (distances in Meters)
    # returns: bField, the 3D vector of magnetic flux density as would be reported by the measurement point in Tesla
    measurementRotMtxInverse = htm_originToMeasurementPoint[:3, :3].T
    htm_originToMeasurementPoint_inverse = np.zeros((4, 4))
    htm_originToMeasurementPoint_inverse[:3, :3] = measurementRotMtxInverse
    htm_originToMeasurementPoint_inverse[:3, -1] = measurementRotMtxInverse @ -htm_originToMeasurementPoint[:3, -1]
    htm_originToMeasurementPoint_inverse[-1, -1] = 1.
    htm_measurementPointToDipoleCenter = htm_originToMeasurementPoint_inverse @ htm_originToDipoleCenter
    r = htm_measurementPointToDipoleCenter[:3, -1] # displacement vector from measurement point to dipole center in Meteres
    m = htm_originToMeasurementPoint_inverse[:3, :3] @ np.array([0., 0., momentMagnitude]) # magnetic moment vector of the dipole relative to the measurement point in Amps * Meters^2
    rNorm = np.linalg.norm(r)
    return mu0 * muR_air / (4 * np.pi) * (3 * m.dot(r) * r / rNorm ** 5 - m / rNorm ** 3)

# dipoleMagneticFluxDensity_htm > 99% accurate for platonic solids and similarly proportioned shapes at > 1 centroid distance (norm(r)) away
