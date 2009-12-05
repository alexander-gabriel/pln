/*
 * opencog/embodiment/Control/OperationalPetController/LanguageComprehension.h
 *
 * Copyright (C) 2009 Novamente LLC
 * All Rights Reserved
 * Author(s): Samir Araujo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LANGUAGECOMPREHENSION_H
#define LANGUAGECOMPREHENSION_H

#include <opencog/atomspace/AtomSpace.h>
#include <opencog/embodiment/Control/PetInterface.h>
#include <opencog/embodiment/Control/OperationalPetController/OutputRelex.h>
#include <opencog/embodiment/Control/OperationalPetController/FramesToRelexRuleEngine.h>
#include <opencog/embodiment/Control/OperationalPetController/NLGenClient.h>

#include <opencog/guile/SchemeEval.h>

namespace OperationalPetController
{
    class LanguageComprehension 
    {
    public: 
        LanguageComprehension( Control::PetInterface& agent );
        
        virtual ~LanguageComprehension( void );        

        void resolveLatestSentenceReference( void );

        void answerLatestQuestion( void );

        void resolveLatestSentenceCommand( void );

        std::string resolveFrames2Relex( );

    protected:

        HandleSeq getActivePredicateArguments( const std::string& predicateName );
        std::string resolveRelex2Sentence( const std::string& relexInput );

        void init(void);
        void loadFrames(void);

#ifdef HAVE_GUILE
        /** The static elements below will be replaced by a SchemePrimitive soon **/
        static SCM execute(SCM objectObserver, SCM figureSemeNode, SCM groundSemeNode, SCM ground2SemeNode );
#endif
        static void createFrameInstancesFromRelations( AtomSpace& atomSpace, HandleSeq& resultingFrames,
                                                       const std::list<Spatial::LocalSpaceMap2D::SPATIAL_RELATION>& relations,
                                                       const std::string& objectA, const std::string& objectB, const std::string& objectC );
        static Control::PetInterface* localAgent;
        
        Control::PetInterface& agent;
        std::string nlgen_server_host;
        int nlgen_server_port;
        FramesToRelexRuleEngine framesToRelexRuleEngine;
        NLGenClient *nlgenClient;
        bool initialized;

    };

};






#endif // LANGUAGECOMPREHENSION_H
