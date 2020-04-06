/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2018-2019 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    Test-vector

Description
    Some simple tests for vector

\*---------------------------------------------------------------------------*/

#include "vector.H"
#include "IOstreams.H"
#include <algorithm>

using namespace Foam;

void printInfo(const vector& vec)
{
    Info<< "vector : " << vec << nl
        << "magSqr : " << magSqr(vec) << nl;

    Info<< "component"
        << " max:" << cmptMax(vec)
        << " sum:" << cmptSum(vec)
        << " prod:" << cmptProduct(vec)
        << " mag:" << cmptMag(vec)
        << " magSqr:" << cmptMagSqr(vec)
        << nl << nl;
}


void doTest(vector& vec1, vector& vec2)
{
    Info<<"normalised(vector1): " << normalised(vec1) << nl;
    Info<<"vector1: " << vec1 << nl;
    vec1.normalise();
    Info<<"normalised: " << vec1 << nl;

    vector vecsmall((1e-100 * vec1));

    Info<<"small: " << vecsmall << nl;
    Info<<"small normalised: " << normalised(vecsmall) << nl;
    Info<<"small diff: " << (vecsmall.normalise() - vec1) << nl;

    vec1 *= 4.0;

    Info<< "scalar mult: " << vec1 << nl;
    Info<< "addition   : " << (vec1 + vec1) << nl;

    printInfo(vec1);
    printInfo(vec2);

    Info<< "min of " << vec1 << " and " << vec2 << " = "
        << min(vec1, vec2) << nl << nl;
}


template<class VecSpace>
void testIterator(const VecSpace& vs)
{
    Info<< "size: " << vs.size() << " for:";
    for (const auto& val : vs)
    {
        Info<< " " << val;
    }
    Info<< nl;
}


template<class VecSpace>
void testData(const VecSpace& vs)
{
    Info<< "size: " << vs.size() << " for:";

    const auto* data = vs.cdata();
    for
    (
        const auto* endData = data + VecSpace::nComponents;
        data != endData;
        ++data
    )
    {
        Info<< " " << *data;
    }
    Info<< nl;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//  Main program:

int main(int argc, char *argv[])
{
    Info<<"normalised: " << vector(1,2,3).normalise() << nl;
    Info<<"normalised: " << vector(VSMALL,VSMALL,VSMALL).normalise() << nl;
    Info<<"normalised: " <<
        vector(ROOTVSMALL,ROOTVSMALL,ROOTVSMALL).normalise() << nl;

    {
        vector vec1(0.5, 0.5, 0.5);
        vector vec2(0.5, 0.51, -0.5);

        doTest(vec1, vec2);

        testIterator(vec1);
        testIterator(vec2);
        testData(vec2);

        // Use STL algorithm(s)

        std::sort(vec2.begin(), vec2.end());
        Info<< "sorted: " << vec2 << nl;

        std::random_shuffle(vec2.begin(), vec2.end());
        Info<< "shuffled: " << vec2 << nl;

        Info<< "vec1 + vect2 " << vec1 + vec2 << nl;
    }

    Info<< "\nEnd\n" << nl;

    return 0;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
