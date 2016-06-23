//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
//
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR:
//***************************************************************************/

#include "maxProject1.h"

static const Class_ID maxProject1_CLASS_ID(0x9aacfcae, 0x6c2a9f55);

#define PBLOCK_REF	0


class maxProject1 : public FilterKernel
{

public:
	//Constructor/Destructor
	maxProject1();
	virtual ~maxProject1();

	virtual TSTR GetName();

	// Kernel parameter setup and handling
	virtual long GetNFilterParams();
	virtual const TCHAR * GetFilterParamName( long nParam );
	virtual double GetFilterParam( long nParam );
	virtual void SetFilterParam( long nParam, double val );
	virtual const TCHAR * GetDefaultComment();

	virtual void Update(TimeValue t, Interval& valid);

	// Actual kernel function
	virtual double KernelFn( double x, double y );

	// Kernel functionality queries
	virtual long GetKernelSupport();
	virtual long GetKernelSupportY();
	virtual bool Is2DKernel();
	virtual bool IsVariableSz();
	virtual void SetKernelSz( double x, double y = 0.0 );
	virtual void GetKernelSz( double& x, double& y );
	virtual bool IsNormalized();
	virtual bool HasNegativeLobes();

	// Loading/Saving
	virtual IOResult Load(ILoad *iload);
	virtual IOResult Save(ISave *isave);

	//From Animatable
	virtual Class_ID ClassID() {return maxProject1_CLASS_ID;}
	virtual SClass_ID SuperClassID() { return FILTER_KERNEL_CLASS_ID; }
	virtual void GetClassName(TSTR& s) {s = GetString(IDS_CLASS_NAME);}

	virtual RefTargetHandle Clone( RemapDir &remap );
	virtual RefResult NotifyRefChanged(const Interval& changeInt, RefTargetHandle hTarget,
		PartID& partID, RefMessage message, BOOL propagate);


	virtual int NumSubs() { return 1; }
	virtual TSTR SubAnimName(int /*i*/) { return GetString(IDS_PARAMS); }
	virtual Animatable* SubAnim(int /*i*/) { return pblock; }

	// TODO: Maintain the number or references here
	virtual int NumRefs() { return 1; }
	virtual RefTargetHandle GetReference(int i);

	virtual int	NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
	virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock; } // return i'th ParamBlock
	virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock->ID() == id) ? pblock : NULL; } // return id'd ParamBlock

	virtual void DeleteThis();

protected:
	virtual void SetReference(int i, RefTargetHandle rtarg);

private:
	// We store 2 parameters
	double param1, param2;

	// Parameter block
	IParamBlock2	*pblock;	//ref 0
};



class maxProject1ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new maxProject1(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return FILTER_KERNEL_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return maxProject1_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("maxProject1"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetmaxProject1Desc() { 
	static maxProject1ClassDesc maxProject1Desc;
	return &maxProject1Desc; 
}





enum { maxproject1_params };


//TODO: Add enums for various parameters
enum { 
	pb_spin,
	pb_param1,
	pb_param2,
};




static ParamBlockDesc2 maxproject1_param_blk ( maxproject1_params, _T("params"),  0, GetmaxProject1Desc(), 
	P_AUTO_CONSTRUCT, PBLOCK_REF,
	pb_param1, 		_T("param1"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_PARAM1,
		p_default,		0.3f,
		p_end,
	pb_param2, 		_T("param2"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_PARAM2,
		p_default,		0.6f,
		p_end,
	p_end
	);





maxProject1::maxProject1()
:	pblock(nullptr)
{
	GetmaxProject1Desc()->MakeAutoParamBlocks(this);
}

maxProject1::~maxProject1()
{

}

/*===========================================================================*\
 |	Kernel Parameter returns
\*===========================================================================*/

// Number of parameters we support
long maxProject1::GetNFilterParams() { return 2; }

// Get the name of parameter #nParam
const TCHAR * maxProject1::GetFilterParamName( long nParam )
{
	return GetString( nParam ? IDS_PARAM2:IDS_PARAM1 );
}

// Get the value of parameter #nParam
double maxProject1::GetFilterParam( long nParam )
{
	return nParam ? param2 : param1;
}

// Set our parameter variables
void maxProject1::SetFilterParam( long nParam, double val )
{
	if (nParam) {
		param2 = val;
		pblock->SetValue( pb_param2, 0, float( val ) );
 	} else {
		param1 = val;
		pblock->SetValue( pb_param1, 0, float( val ) );
	}
}

void maxProject1::Update(TimeValue t, Interval& valid){
	float val;
	pblock->GetValue( pb_param1, t, val, valid ); param1 = val;
	pblock->GetValue( pb_param2, t, val, valid ); param2 = val;
}

const TCHAR * maxProject1::GetDefaultComment()
{
	return GetString( IDS_COMMENT);
}

IOResult maxProject1::Load(ILoad *iload)
{
	FilterKernel::Load(iload);
	return IO_OK;
}
IOResult maxProject1::Save(ISave *isave)
{
	FilterKernel::Save(isave);
	return IO_OK;
}


RefResult maxProject1::NotifyRefChanged(
		const Interval& /*changeInt*/, RefTargetHandle hTarget,
		PartID& /*partID*/,  RefMessage message, BOOL /*propagate*/) 
{
	switch (message) {
		case REFMSG_CHANGE:
			maxproject1_param_blk.InvalidateUI();
			break;
		case REFMSG_TARGET_DELETED:
			if (hTarget == pblock)
			{
				pblock = nullptr;
			}
			break;
		}
	return REF_SUCCEED;
}

RefTargetHandle maxProject1::Clone( RemapDir &remap )
{
	maxProject1* newObj = new maxProject1();
	newObj->ReplaceReference(0,remap.CloneRef(pblock));
	BaseClone(this, newObj, remap);
	return (RefTargetHandle)newObj;
}



/*===========================================================================*\
 |	Calculate a result
\*===========================================================================*/

double maxProject1::KernelFn( double x, double )
{
	if ( x < param1 ) return 1.0;
	if ( x > param2 ) return 1.0;
	else return 0.0;
}


/*===========================================================================*\
 |	Kernel functionality queries
\*===========================================================================*/

// Integer number of pixels from center to filter 0 edge.
// Must not truncate filter x dimension for 2D filters
long maxProject1::GetKernelSupport(){ return 1; }

// For 2d returns y support, for 1d returns 0
long maxProject1::GetKernelSupportY(){ return 0; }

// Are we 2D or Variable Size?
bool maxProject1::Is2DKernel(){ return FALSE; }
bool maxProject1::IsVariableSz(){ return FALSE; }

// 1-D filters ignore the y parameter, return it as 0.0
void maxProject1::SetKernelSz( double /*x*/, double /*y*/){}
void maxProject1::GetKernelSz( double& x, double& y ){ x = 0.5; y = 0.0; }

// Returning true will disable the built-in normalizer
bool maxProject1::IsNormalized(){ return FALSE; }

// This is for possible future optimizations
bool maxProject1::HasNegativeLobes(){ return FALSE; }

void maxProject1::SetReference( int i, RefTargetHandle rtarg )
{
	if (i == PBLOCK_REF)
	{
		pblock = (IParamBlock2*)rtarg;
	}
}

RefTargetHandle maxProject1::GetReference( int i)
{
	if (i == PBLOCK_REF)
	{
		return pblock;
	}
	return nullptr;
}

void maxProject1::DeleteThis()
{
	delete this;
}

TSTR maxProject1::GetName()
{
	return GetString(IDS_CLASS_NAME);
}