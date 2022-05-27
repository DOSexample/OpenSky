// Copyright (c) 2004-2009 Sundog Software, LLC. All rights reserved worldwide.

/** \file CloudLayerFactory.h
   \brief Instantiates specific types of CloudLayer objects.
 */

#ifndef CLOUD_LAYER_FACTORY_H
#define CLOUD_LAYER_FACTORY_H

#include "Atmosphere.h"
#include "CloudTypes.h"
#include <iostream>

namespace SilverLining
{
class CloudLayer;

/** A class factory for CloudLayer objects.

   Call CloudLayerFactory::Create to instantiate a CloudLayer object, which may then be configured,
   seeded, and submitted to the AtmosphericConditions. CloudLayer is a virtual base class, so this
   is the only mechanism for creating specific cloud layer types.
 */
class CloudLayerFactory
{
public:
/** Instantiate a CloudLayer for a given cloud type. Currently supported #CloudTypes include:

   \li CloudTypes::CIRROCUMULUS - High planar cloud puffs.
   \li CloudTypes::CIRRUS_FIBRATUS - High, wispy cirrus clouds.
   \li CloudTypes::STRATUS - Low clouds represented as a slab.
   \li CloudTypes::CUMULONIMBUS_CAPPILATUS - A large thunderhead with lightning and rain.
   \li CloudTypes::CUMULUS_MEDIOCRIS - Small, puffy clouds.
   \li CloudTypes::CUMULUS_CONGESTUS - Larger cumulus clouds with flattened bottoms.

   \param layerType The type of cloud deck to create, must be of the #CloudTypes enumeration.
   \return A pointer to a new CloudLayer for the specified type.
 */
static CloudLayer *Create(CloudTypes layerType);

/** Flattens a cloud layer to a stream buffer. */
static bool Serialize(CloudLayer *layer, std::ostream& stream);

/** Restores a cloud layer from a stream buffer written with Serialize() */
static CloudLayer *Unserialize(const Atmosphere& atm, std::istream& stream);
};
}

#endif