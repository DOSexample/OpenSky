// Copyright (c) 2004-2010 Sundog Software, LLC. All rights reserved worldwide.

/** \file CloudTypes.h
   \brief Defines the enumerated values of cloud layer types that may be passed
   to CloudLayerFactory::Create.
 */

#ifndef CLOUD_TYPES_H
#define CLOUD_TYPES_H

/*! Cloud types suitable for passing into CloudLayerFactory::Create */
enum CloudTypes
{
    CIRROCUMULUS,               /*!<  High planar cloud puffs */
    CIRRUS_FIBRATUS,            /*!<  High, thicker and fibrous clouds that signal changing weather */
    STRATUS,                    /*!<  Low clouds represented as a slab */
    CUMULUS_MEDIOCRIS,          /*!<  Low, puffy clouds on fair days */
    CUMULUS_CONGESTUS,          /*!<  Large cumulus clouds that could turn into a thunderhead */
    CUMULONIMBUS_CAPPILATUS,    /*!<  Big storm clouds. */
    NUM_CLOUD_TYPES             /*!<  Total number of cloud types. */
};

#endif