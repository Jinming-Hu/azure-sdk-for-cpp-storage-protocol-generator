
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/***************************************************************
 * ALL THE CODE IN THIS FILE IS HANDWRITTEN, NOT AUTO-GENERATED.
 **************************************************************/

#pragma once


#include <string>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>

#include "libxml/tree.h"

#include "http/http.hpp"


namespace Azure
{
namespace Storage
{
namespace Blobs
{

class BlobRestClient { public:

constexpr static const char* k_HeaderApiVersionParameter = "x-ms-version";
constexpr static const char* k_HeaderBlobCacheControl = "x-ms-blob-cache-control";
constexpr static const char* k_HeaderBlobConditionAppendPos = "x-ms-blob-condition-appendpos";
constexpr static const char* k_HeaderBlobConditionMaxSize = "x-ms-blob-condition-maxsize";
constexpr static const char* k_HeaderBlobPublicAccess = "x-ms-blob-public-access";
constexpr static const char* k_HeaderAccessTierRequired = "x-ms-access-tier";
constexpr static const char* k_HeaderAccessTierOptional = "x-ms-access-tier";
constexpr static const char* k_HeaderPremiumPageBlobAccessTierOptional = "x-ms-access-tier";
constexpr static const char* k_HeaderRehydratePriority = "x-ms-rehydrate-priority";
constexpr static const char* k_HeaderBlobContentDisposition = "x-ms-blob-content-disposition";
constexpr static const char* k_HeaderBlobContentEncoding = "x-ms-blob-content-encoding";
constexpr static const char* k_HeaderBlobContentLanguage = "x-ms-blob-content-language";
constexpr static const char* k_HeaderBlobContentLengthOptional = "x-ms-blob-content-length";
constexpr static const char* k_HeaderBlobContentLengthRequired = "x-ms-blob-content-length";
constexpr static const char* k_HeaderBlobContentMD5 = "x-ms-blob-content-md5";
constexpr static const char* k_HeaderBlobContentType = "x-ms-blob-content-type";
constexpr static const char* k_HeaderBlobSequenceNumber = "x-ms-blob-sequence-number";
constexpr static const char* k_QueryBlockId = "blockid";
constexpr static const char* k_QueryBlockListType = "blocklisttype";
constexpr static const char* k_QueryContinuation = "continuation";
constexpr static const char* k_QueryCopyId = "copyid";
constexpr static const char* k_HeaderClientRequestId = "x-ms-client-request-id";
constexpr static const char* k_HeaderContentCrc64 = "x-ms-content-crc64";
constexpr static const char* k_HeaderContentLength = "Content-Length";
constexpr static const char* k_HeaderContentMD5 = "Content-MD5";
constexpr static const char* k_HeaderCopySource = "x-ms-copy-source";
constexpr static const char* k_HeaderDeleteSnapshots = "x-ms-delete-snapshots";
constexpr static const char* k_QueryDelimiter = "delimiter";
constexpr static const char* k_HeaderDirectoryProperties = "x-ms-properties";
constexpr static const char* k_HeaderEncryptionKey = "x-ms-encryption-key";
constexpr static const char* k_HeaderEncryptionKeySha256 = "x-ms-encryption-key-sha256";
constexpr static const char* k_HeaderEncryptionAlgorithm = "x-ms-encryption-algorithm";
constexpr static const char* k_HeaderFileRenameSource = "x-ms-rename-source";
constexpr static const char* k_HeaderGetRangeContentMD5 = "x-ms-range-get-content-md5";
constexpr static const char* k_HeaderGetRangeContentCRC64 = "x-ms-range-get-content-crc64";
constexpr static const char* k_HeaderIfMatch = "If-Match";
constexpr static const char* k_HeaderIfModifiedSince = "If-Modified-Since";
constexpr static const char* k_HeaderIfNoneMatch = "If-None-Match";
constexpr static const char* k_HeaderIfUnmodifiedSince = "If-Unmodified-Since";
constexpr static const char* k_HeaderIfSequenceNumberEqualTo = "x-ms-if-sequence-number-eq";
constexpr static const char* k_HeaderIfSequenceNumberLessThan = "x-ms-if-sequence-number-lt";
constexpr static const char* k_HeaderIfSequenceNumberLessThanOrEqualTo = "x-ms-if-sequence-number-le";
constexpr static const char* k_QueryListContainersInclude = "include";
constexpr static const char* k_HeaderLeaseBreakPeriod = "x-ms-lease-break-period";
constexpr static const char* k_HeaderLeaseDuration = "x-ms-lease-duration";
constexpr static const char* k_HeaderLeaseIdOptional = "x-ms-lease-id";
constexpr static const char* k_HeaderLeaseIdRequired = "x-ms-lease-id";
constexpr static const char* k_HeaderOwner = "x-ms-owner";
constexpr static const char* k_HeaderGroup = "x-ms-group";
constexpr static const char* k_QueryUpn = "upn";
constexpr static const char* k_QueryMarker = "marker";
constexpr static const char* k_QueryMaxResults = "maxresults";
constexpr static const char* k_HeaderMetadata = "x-ms-meta";
constexpr static const char* k_HeaderMultipartContentType = "Content-Type";
constexpr static const char* k_QueryPathRenameMode = "mode";
constexpr static const char* k_HeaderPosixPermissions = "x-ms-permissions";
constexpr static const char* k_HeaderPosixAcl = "x-ms-acl";
constexpr static const char* k_HeaderPosixUmask = "x-ms-umask";
constexpr static const char* k_QueryPrefix = "prefix";
constexpr static const char* k_QueryPrevSnapshot = "prevsnapshot";
constexpr static const char* k_HeaderProposedLeaseIdOptional = "x-ms-proposed-lease-id";
constexpr static const char* k_HeaderProposedLeaseIdRequired = "x-ms-proposed-lease-id";
constexpr static const char* k_HeaderRange = "x-ms-range";
constexpr static const char* k_HeaderRangeRequiredPutPageFromUrl = "x-ms-range";
constexpr static const char* k_QueryRecursiveDirectoryDelete = "recursive";
constexpr static const char* k_HeaderSequenceNumberAction = "x-ms-sequence-number-action";
constexpr static const char* k_QuerySnapshot = "snapshot";
constexpr static const char* k_HeaderSourceContentMD5 = "x-ms-source-content-md5";
constexpr static const char* k_HeaderSourceContentCRC64 = "x-ms-source-content-crc64";
constexpr static const char* k_HeaderSourceRange = "x-ms-source-range";
constexpr static const char* k_HeaderSourceRangeRequiredPutPageFromUrl = "x-ms-source-range";
constexpr static const char* k_HeaderSourceIfMatch = "x-ms-source-if-match";
constexpr static const char* k_HeaderSourceIfModifiedSince = "x-ms-source-if-modified-since";
constexpr static const char* k_HeaderSourceIfNoneMatch = "x-ms-source-if-none-match";
constexpr static const char* k_HeaderSourceIfUnmodifiedSince = "x-ms-source-if-unmodified-since";
constexpr static const char* k_HeaderSourceLeaseId = "x-ms-source-lease-id";
constexpr static const char* k_HeaderSourceUrl = "x-ms-copy-source";
constexpr static const char* k_QueryTimeout = "timeout";
constexpr static const char* k_HeaderXMsCacheControl = "x-ms-cache-control";
constexpr static const char* k_HeaderXMsContentType = "x-ms-content-type";
constexpr static const char* k_HeaderXMsContentEncoding = "x-ms-content-encoding";
constexpr static const char* k_HeaderXMsContentLanguage = "x-ms-content-language";
constexpr static const char* k_HeaderXMsContentDisposition = "x-ms-content-disposition";

// Key information
struct KeyInfo
{
std::string Start; // The date-time the key is active in ISO 8601 UTC time
std::string Expiry; // The date-time the key expires in ISO 8601 UTC time

static XmlNode SerializeToXml(const KeyInfo& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Start", object.Start));
result.AddChildNode(XmlNode("Expiry", object.Expiry));
return result;
}
};  // struct KeyInfo

// A user delegation key
struct UserDelegationKey
{
std::string SignedOid; // The Azure Active Directory object ID in GUID format.
std::string SignedTid; // The Azure Active Directory tenant ID in GUID format
std::string SignedStart; // The date-time the key is active
std::string SignedExpiry; // The date-time the key expires
std::string SignedService; // Abbreviation of the Azure Storage service that accepts the key
std::string SignedVersion; // The service version that created the key
std::string Value; // The key as a base64 string

static XmlNode SerializeToXml(const UserDelegationKey& object)
{
XmlNode result;
result.AddChildNode(XmlNode("SignedOid", object.SignedOid));
result.AddChildNode(XmlNode("SignedTid", object.SignedTid));
result.AddChildNode(XmlNode("SignedStart", object.SignedStart));
result.AddChildNode(XmlNode("SignedExpiry", object.SignedExpiry));
result.AddChildNode(XmlNode("SignedService", object.SignedService));
result.AddChildNode(XmlNode("SignedVersion", object.SignedVersion));
result.AddChildNode(XmlNode("Value", object.Value));
return result;
}
};  // struct UserDelegationKey

enum class PublicAccessType
{
Container,
Blob,
Unknown
};

static std::string PublicAccessTypeToString(const PublicAccessType& publicAccessType)
{
    switch (publicAccessType)
    {case PublicAccessType::Container: return "Container";case PublicAccessType::Blob: return "Blob";default: return std::string(); }}

static PublicAccessType PublicAccessTypeFromString(const std::string& publicAccessType)
{if (publicAccessType == "Container") { return PublicAccessType::Container; }if (publicAccessType == "Blob") { return PublicAccessType::Blob; }throw std::runtime_error("Cannot convert " + publicAccessType + " to PublicAccessType");};  // enum class PublicAccessType

enum class CopyStatus
{
Pending,
Success,
Aborted,
Failed,
Unknown
};

static std::string CopyStatusToString(const CopyStatus& copyStatus)
{
    switch (copyStatus)
    {case CopyStatus::Pending: return "Pending";case CopyStatus::Success: return "Success";case CopyStatus::Aborted: return "Aborted";case CopyStatus::Failed: return "Failed";default: return std::string(); }}

static CopyStatus CopyStatusFromString(const std::string& copyStatus)
{if (copyStatus == "Pending") { return CopyStatus::Pending; }if (copyStatus == "Success") { return CopyStatus::Success; }if (copyStatus == "Aborted") { return CopyStatus::Aborted; }if (copyStatus == "Failed") { return CopyStatus::Failed; }throw std::runtime_error("Cannot convert " + copyStatus + " to CopyStatus");};  // enum class CopyStatus

enum class LeaseDuration
{
Infinite,
Fixed,
Unknown
};

static std::string LeaseDurationToString(const LeaseDuration& leaseDuration)
{
    switch (leaseDuration)
    {case LeaseDuration::Infinite: return "Infinite";case LeaseDuration::Fixed: return "Fixed";default: return std::string(); }}

static LeaseDuration LeaseDurationFromString(const std::string& leaseDuration)
{if (leaseDuration == "Infinite") { return LeaseDuration::Infinite; }if (leaseDuration == "Fixed") { return LeaseDuration::Fixed; }throw std::runtime_error("Cannot convert " + leaseDuration + " to LeaseDuration");};  // enum class LeaseDuration

enum class LeaseState
{
Available,
Leased,
Expired,
Breaking,
Broken,
Unknown
};

static std::string LeaseStateToString(const LeaseState& leaseState)
{
    switch (leaseState)
    {case LeaseState::Available: return "Available";case LeaseState::Leased: return "Leased";case LeaseState::Expired: return "Expired";case LeaseState::Breaking: return "Breaking";case LeaseState::Broken: return "Broken";default: return std::string(); }}

static LeaseState LeaseStateFromString(const std::string& leaseState)
{if (leaseState == "Available") { return LeaseState::Available; }if (leaseState == "Leased") { return LeaseState::Leased; }if (leaseState == "Expired") { return LeaseState::Expired; }if (leaseState == "Breaking") { return LeaseState::Breaking; }if (leaseState == "Broken") { return LeaseState::Broken; }throw std::runtime_error("Cannot convert " + leaseState + " to LeaseState");};  // enum class LeaseState

enum class LeaseStatus
{
Locked,
Unlocked,
Unknown
};

static std::string LeaseStatusToString(const LeaseStatus& leaseStatus)
{
    switch (leaseStatus)
    {case LeaseStatus::Locked: return "Locked";case LeaseStatus::Unlocked: return "Unlocked";default: return std::string(); }}

static LeaseStatus LeaseStatusFromString(const std::string& leaseStatus)
{if (leaseStatus == "Locked") { return LeaseStatus::Locked; }if (leaseStatus == "Unlocked") { return LeaseStatus::Unlocked; }throw std::runtime_error("Cannot convert " + leaseStatus + " to LeaseStatus");};  // enum class LeaseStatus

struct StorageError
{
std::string Message;
ErrorCode Code;

static StorageError CreateFromXml(const XmlNode& node)
{
StorageError result;
result.Message = node["Message"].value;
result.Code = StorageErrorCodeFromString(node["ErrorCode"].value);
return result;
}

static XmlNode SerializeToXml(const StorageError& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Message", object.Message));
result.AddChildNode(XmlNode("ErrorCode", StorageErrorCodeToString(object.Code)));
return result;
}
};  // struct StorageError

struct DataLakeStorageError
{

// The service error response object.
struct Error
{
std::string Code; // The service error code.
std::string Message; // The service error message.

static XmlNode SerializeToXml(const Error& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Code", object.Code));
result.AddChildNode(XmlNode("Message", object.Message));
return result;
}
};  // struct Error

Error Error; // The service error response object.

static XmlNode SerializeToXml(const DataLakeStorageError& object)
{
XmlNode result;
result.AddChildNode(XmlNode("error", object.Error));
return result;
}
};  // struct DataLakeStorageError

// An Access policy
struct AccessPolicy
{
std::string Start; // the date-time the policy is active
std::string Expiry; // the date-time the policy expires
std::string Permission; // the permissions for the acl policy

static AccessPolicy CreateFromXml(const XmlNode& node)
{
AccessPolicy result;
result.Start = node["Start"].value;
result.Expiry = node["Expiry"].value;
result.Permission = node["Permission"].value;
return result;
}

static XmlNode SerializeToXml(const AccessPolicy& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Start", object.Start));
result.AddChildNode(XmlNode("Expiry", object.Expiry));
result.AddChildNode(XmlNode("Permission", object.Permission));
return result;
}
};  // struct AccessPolicy

enum class AccessTier
{
P4,
P6,
P10,
P15,
P20,
P30,
P40,
P50,
P60,
P70,
P80,
Hot,
Cool,
Archive,
Unknown
};

static std::string AccessTierToString(const AccessTier& accessTier)
{
    switch (accessTier)
    {case AccessTier::P4: return "P4";case AccessTier::P6: return "P6";case AccessTier::P10: return "P10";case AccessTier::P15: return "P15";case AccessTier::P20: return "P20";case AccessTier::P30: return "P30";case AccessTier::P40: return "P40";case AccessTier::P50: return "P50";case AccessTier::P60: return "P60";case AccessTier::P70: return "P70";case AccessTier::P80: return "P80";case AccessTier::Hot: return "Hot";case AccessTier::Cool: return "Cool";case AccessTier::Archive: return "Archive";default: return std::string(); }}

static AccessTier AccessTierFromString(const std::string& accessTier)
{if (accessTier == "P4") { return AccessTier::P4; }if (accessTier == "P6") { return AccessTier::P6; }if (accessTier == "P10") { return AccessTier::P10; }if (accessTier == "P15") { return AccessTier::P15; }if (accessTier == "P20") { return AccessTier::P20; }if (accessTier == "P30") { return AccessTier::P30; }if (accessTier == "P40") { return AccessTier::P40; }if (accessTier == "P50") { return AccessTier::P50; }if (accessTier == "P60") { return AccessTier::P60; }if (accessTier == "P70") { return AccessTier::P70; }if (accessTier == "P80") { return AccessTier::P80; }if (accessTier == "Hot") { return AccessTier::Hot; }if (accessTier == "Cool") { return AccessTier::Cool; }if (accessTier == "Archive") { return AccessTier::Archive; }throw std::runtime_error("Cannot convert " + accessTier + " to AccessTier");};  // enum class AccessTier

enum class ArchiveStatus
{
RehydratePendingToHot,
RehydratePendingToCool,
Unknown
};

static std::string ArchiveStatusToString(const ArchiveStatus& archiveStatus)
{
    switch (archiveStatus)
    {case ArchiveStatus::RehydratePendingToHot: return "RehydratePendingToHot";case ArchiveStatus::RehydratePendingToCool: return "RehydratePendingToCool";default: return std::string(); }}

static ArchiveStatus ArchiveStatusFromString(const std::string& archiveStatus)
{if (archiveStatus == "RehydratePendingToHot") { return ArchiveStatus::RehydratePendingToHot; }if (archiveStatus == "RehydratePendingToCool") { return ArchiveStatus::RehydratePendingToCool; }throw std::runtime_error("Cannot convert " + archiveStatus + " to ArchiveStatus");};  // enum class ArchiveStatus

// An Azure Storage blob
struct BlobItem
{
std::string Name;
bool Deleted;
std::string Snapshot;
BlobProperties Properties;
BlobMetadata Metadata;

static BlobItem CreateFromXml(const XmlNode& node)
{
BlobItem result;
result.Name = node["Name"].value;
result.Deleted = node["Deleted"].value;
result.Snapshot = node["Snapshot"].value;
result.Properties = BlobProperties::CreateFromXml(node["Properties"]);
for (const auto& n : node["Metadata"].value)
{
result.Metadata[n.key] = n.value;
}
return result;
}

static XmlNode SerializeToXml(const BlobItem& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Name", object.Name));
result.AddChildNode(XmlNode("Deleted", object.Deleted));
result.AddChildNode(XmlNode("Snapshot", object.Snapshot));
result.AddChildNode(BlobProperties::SerializeToXml(object.Properties));
return result;
}
};  // struct BlobItem

// Properties of a blob
struct BlobProperties
{
std::string CreationTime;
std::string LastModified;
std::string Etag;
uint32_t ContentLength; // Size in bytes
std::string ContentType;
std::string ContentEncoding;
std::string ContentLanguage;
std::string ContentMD5;
std::string ContentDisposition;
std::string CacheControl;
uint32_t XMsBlobSequenceNumber;
std::string BlobType;
LeaseStatus LeaseStatus;
LeaseState LeaseState;
LeaseDuration LeaseDuration;
std::string CopyId;
CopyStatus CopyStatus;
std::string CopySource;
std::string CopyProgress;
std::string CopyCompletionTime;
std::string CopyStatusDescription;
bool ServerEncrypted;
bool IncrementalCopy;
std::string DestinationSnapshot;
std::string DeletedTime;
uint32_t RemainingRetentionDays;
AccessTier AccessTier;
bool AccessTierInferred;
ArchiveStatus ArchiveStatus;
std::string CustomerProvidedKeySha256;
std::string AccessTierChangeTime;

static BlobProperties CreateFromXml(const XmlNode& node)
{
BlobProperties result;
result.CreationTime = node["Creation-Time"].value;
result.LastModified = node["Last-Modified"].value;
result.Etag = node["Etag"].value;
result.ContentLength = node["Content-Length"].value;
result.ContentType = node["Content-Type"].value;
result.ContentEncoding = node["Content-Encoding"].value;
result.ContentLanguage = node["Content-Language"].value;
result.ContentMD5 = node["Content-MD5"].value;
result.ContentDisposition = node["Content-Disposition"].value;
result.CacheControl = node["Cache-Control"].value;
result.XMsBlobSequenceNumber = node["x-ms-blob-sequence-number"].value;
result.BlobType = node["BlobType"].value;
result.LeaseStatus = LeaseStatusTypeFromString(node["LeaseStatus"].value);
result.LeaseState = LeaseStateTypeFromString(node["LeaseState"].value);
result.LeaseDuration = LeaseDurationTypeFromString(node["LeaseDuration"].value);
result.CopyId = node["CopyId"].value;
result.CopyStatus = CopyStatusTypeFromString(node["CopyStatus"].value);
result.CopySource = node["CopySource"].value;
result.CopyProgress = node["CopyProgress"].value;
result.CopyCompletionTime = node["CopyCompletionTime"].value;
result.CopyStatusDescription = node["CopyStatusDescription"].value;
result.ServerEncrypted = node["ServerEncrypted"].value;
result.IncrementalCopy = node["IncrementalCopy"].value;
result.DestinationSnapshot = node["DestinationSnapshot"].value;
result.DeletedTime = node["DeletedTime"].value;
result.RemainingRetentionDays = node["RemainingRetentionDays"].value;
result.AccessTier = AccessTierFromString(node["AccessTier"].value);
result.AccessTierInferred = node["AccessTierInferred"].value;
result.ArchiveStatus = ArchiveStatusFromString(node["ArchiveStatus"].value);
result.CustomerProvidedKeySha256 = node["CustomerProvidedKeySha256"].value;
result.AccessTierChangeTime = node["AccessTierChangeTime"].value;
return result;
}

static XmlNode SerializeToXml(const BlobProperties& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Creation-Time", object.CreationTime));
result.AddChildNode(XmlNode("Last-Modified", object.LastModified));
result.AddChildNode(XmlNode("Etag", object.Etag));
result.AddChildNode(XmlNode("Content-Length", object.ContentLength));
result.AddChildNode(XmlNode("Content-Type", object.ContentType));
result.AddChildNode(XmlNode("Content-Encoding", object.ContentEncoding));
result.AddChildNode(XmlNode("Content-Language", object.ContentLanguage));
result.AddChildNode(XmlNode("Content-MD5", object.ContentMD5));
result.AddChildNode(XmlNode("Content-Disposition", object.ContentDisposition));
result.AddChildNode(XmlNode("Cache-Control", object.CacheControl));
result.AddChildNode(XmlNode("x-ms-blob-sequence-number", object.XMsBlobSequenceNumber));
result.AddChildNode(XmlNode("BlobType", object.BlobType));
result.AddChildNode(XmlNode("LeaseStatus", LeaseStatusTypeToString(object.LeaseStatus)));
result.AddChildNode(XmlNode("LeaseState", LeaseStateTypeToString(object.LeaseState)));
result.AddChildNode(XmlNode("LeaseDuration", LeaseDurationTypeToString(object.LeaseDuration)));
result.AddChildNode(XmlNode("CopyId", object.CopyId));
result.AddChildNode(XmlNode("CopyStatus", CopyStatusTypeToString(object.CopyStatus)));
result.AddChildNode(XmlNode("CopySource", object.CopySource));
result.AddChildNode(XmlNode("CopyProgress", object.CopyProgress));
result.AddChildNode(XmlNode("CopyCompletionTime", object.CopyCompletionTime));
result.AddChildNode(XmlNode("CopyStatusDescription", object.CopyStatusDescription));
result.AddChildNode(XmlNode("ServerEncrypted", object.ServerEncrypted));
result.AddChildNode(XmlNode("IncrementalCopy", object.IncrementalCopy));
result.AddChildNode(XmlNode("DestinationSnapshot", object.DestinationSnapshot));
result.AddChildNode(XmlNode("DeletedTime", object.DeletedTime));
result.AddChildNode(XmlNode("RemainingRetentionDays", object.RemainingRetentionDays));
result.AddChildNode(XmlNode("AccessTier", AccessTierToString(object.AccessTier)));
result.AddChildNode(XmlNode("AccessTierInferred", object.AccessTierInferred));
result.AddChildNode(XmlNode("ArchiveStatus", ArchiveStatusToString(object.ArchiveStatus)));
result.AddChildNode(XmlNode("CustomerProvidedKeySha256", object.CustomerProvidedKeySha256));
result.AddChildNode(XmlNode("AccessTierChangeTime", object.AccessTierChangeTime));
return result;
}
};  // struct BlobProperties

// An enumeration of blobs
struct ListBlobsFlatSegmentResponse
{
std::string ServiceEndpoint;
std::string ContainerName;
std::string Prefix;
std::string Marker;
uint32_t MaxResults;
BlobFlatListSegment Segment;
std::string NextMarker;

static ListBlobsFlatSegmentResponse CreateFromXml(const XmlNode& node)
{
ListBlobsFlatSegmentResponse result;
result.ServiceEndpoint = node.getAttribute("ServiceEndpoint");
result.ContainerName = node.getAttribute("ContainerName");
result.Prefix = node["Prefix"].value;
result.Marker = node["Marker"].value;
result.MaxResults = node["MaxResults"].value;
result.Segment = BlobFlatListSegment::CreateFromXml(node["Blobs"]);
result.NextMarker = node["NextMarker"].value;
return result;
}

static XmlNode SerializeToXml(const ListBlobsFlatSegmentResponse& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Prefix", object.Prefix));
result.AddChildNode(XmlNode("Marker", object.Marker));
result.AddChildNode(XmlNode("MaxResults", object.MaxResults));
result.AddChildNode(BlobFlatListSegment::SerializeToXml(object.Segment));
result.AddChildNode(XmlNode("NextMarker", object.NextMarker));
return result;
}
};  // struct ListBlobsFlatSegmentResponse

// An enumeration of blobs
struct ListBlobsHierarchySegmentResponse
{
std::string ServiceEndpoint;
std::string ContainerName;
std::string Prefix;
std::string Marker;
uint32_t MaxResults;
std::string Delimiter;
BlobHierarchyListSegment Segment;
std::string NextMarker;

static ListBlobsHierarchySegmentResponse CreateFromXml(const XmlNode& node)
{
ListBlobsHierarchySegmentResponse result;
result.ServiceEndpoint = node.getAttribute("ServiceEndpoint");
result.ContainerName = node.getAttribute("ContainerName");
result.Prefix = node["Prefix"].value;
result.Marker = node["Marker"].value;
result.MaxResults = node["MaxResults"].value;
result.Delimiter = node["Delimiter"].value;
result.Segment = BlobHierarchyListSegment::CreateFromXml(node["Blobs"]);
result.NextMarker = node["NextMarker"].value;
return result;
}

static XmlNode SerializeToXml(const ListBlobsHierarchySegmentResponse& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Prefix", object.Prefix));
result.AddChildNode(XmlNode("Marker", object.Marker));
result.AddChildNode(XmlNode("MaxResults", object.MaxResults));
result.AddChildNode(XmlNode("Delimiter", object.Delimiter));
result.AddChildNode(BlobHierarchyListSegment::SerializeToXml(object.Segment));
result.AddChildNode(XmlNode("NextMarker", object.NextMarker));
return result;
}
};  // struct ListBlobsHierarchySegmentResponse

struct BlobFlatListSegment
{
std::vector<BlobItem> BlobItems;

static BlobFlatListSegment CreateFromXml(const XmlNode& node)
{
BlobFlatListSegment result;
for (const auto& n : node)
{
result.BlobItems.push_back(BlobItem::CreateFromXml(n["Blob"]));
}
return result;
}

static XmlNode SerializeToXml(const BlobFlatListSegment& object)
{
XmlNode result;
result.addChildNode(XmlEmptyArrayNode("BlobItems"));
for (const auto& item : object.BlobItems)
{
result["BlobItems"].AddChildNode(BlobItem::SerializeToXml(item));
}
return result;
}
};  // struct BlobFlatListSegment

struct BlobHierarchyListSegment
{
std::vector<BlobPrefix> BlobPrefixes;
std::vector<BlobItem> BlobItems;

static BlobHierarchyListSegment CreateFromXml(const XmlNode& node)
{
BlobHierarchyListSegment result;
for (const auto& n : node)
{
result.BlobPrefixes.push_back(BlobPrefix::CreateFromXml(n["BlobPrefix"]));
}
for (const auto& n : node)
{
result.BlobItems.push_back(BlobItem::CreateFromXml(n["Blob"]));
}
return result;
}

static XmlNode SerializeToXml(const BlobHierarchyListSegment& object)
{
XmlNode result;
result.addChildNode(XmlEmptyArrayNode("BlobPrefixes"));
for (const auto& item : object.BlobPrefixes)
{
result["BlobPrefixes"].AddChildNode(BlobPrefix::SerializeToXml(item));
}
result.addChildNode(XmlEmptyArrayNode("BlobItems"));
for (const auto& item : object.BlobItems)
{
result["BlobItems"].AddChildNode(BlobItem::SerializeToXml(item));
}
return result;
}
};  // struct BlobHierarchyListSegment

struct BlobPrefix
{
std::string Name;

static BlobPrefix CreateFromXml(const XmlNode& node)
{
BlobPrefix result;
result.Name = node["Name"].value;
return result;
}

static XmlNode SerializeToXml(const BlobPrefix& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Name", object.Name));
return result;
}
};  // struct BlobPrefix

// Represents a single block in a block blob.  It describes the block's ID and size.
struct Block
{
std::string Name; // The base64 encoded block ID.
uint32_t Size; // The block size in bytes.

static XmlNode SerializeToXml(const Block& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Name", object.Name));
result.AddChildNode(XmlNode("Size", object.Size));
return result;
}
};  // struct Block

struct BlockList
{
std::vector<Block> CommittedBlocks;
std::vector<Block> UncommittedBlocks;

static XmlNode SerializeToXml(const BlockList& object)
{
XmlNode result;
result.addChildNode(XmlEmptyArrayNode("CommittedBlocks"));
for (const auto& item : object.CommittedBlocks)
{
result["CommittedBlocks"].AddChildNode(Block::SerializeToXml(item));
}
result.addChildNode(XmlEmptyArrayNode("UncommittedBlocks"));
for (const auto& item : object.UncommittedBlocks)
{
result["UncommittedBlocks"].AddChildNode(Block::SerializeToXml(item));
}
return result;
}
};  // struct BlockList

struct BlockLookupList
{
std::vector<std::string> Committed;
std::vector<std::string> Uncommitted;
std::vector<std::string> Latest;

static BlockLookupList CreateFromXml(const XmlNode& node)
{
BlockLookupList result;
for (const auto& n : node)
{
result.Committed.push_back(n["Committed"].value);
}
for (const auto& n : node)
{
result.Uncommitted.push_back(n["Uncommitted"].value);
}
for (const auto& n : node)
{
result.Latest.push_back(n["Latest"].value);
}
return result;
}

static XmlNode SerializeToXml(const BlockLookupList& object)
{
XmlNode result;
result.addChildNode(XmlEmptyArrayNode("Committed"));
for (const auto& item : object.Committed)
{
result["Committed"].AddChildNode(XmlNode("Committed", item));
}
result.addChildNode(XmlEmptyArrayNode("Uncommitted"));
for (const auto& item : object.Uncommitted)
{
result["Uncommitted"].AddChildNode(XmlNode("Uncommitted", item));
}
result.addChildNode(XmlEmptyArrayNode("Latest"));
for (const auto& item : object.Latest)
{
result["Latest"].AddChildNode(XmlNode("Latest", item));
}
return result;
}
};  // struct BlockLookupList

// An Azure Storage container
struct ContainerItem
{
std::string Name;
ContainerProperties Properties;
ContainerMetadata Metadata;

static ContainerItem CreateFromXml(const XmlNode& node)
{
ContainerItem result;
result.Name = node["Name"].value;
result.Properties = ContainerProperties::CreateFromXml(node["Properties"]);
for (const auto& n : node["Metadata"].value)
{
result.Metadata[n.key] = n.value;
}
return result;
}

static XmlNode SerializeToXml(const ContainerItem& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Name", object.Name));
result.AddChildNode(ContainerProperties::SerializeToXml(object.Properties));
return result;
}
};  // struct ContainerItem

// Properties of a container
struct ContainerProperties
{
std::string LastModified;
std::string Etag;
LeaseStatus LeaseStatus;
LeaseState LeaseState;
LeaseDuration LeaseDuration;
PublicAccessType PublicAccess;
bool HasImmutabilityPolicy;
bool HasLegalHold;

static ContainerProperties CreateFromXml(const XmlNode& node)
{
ContainerProperties result;
result.LastModified = node["Last-Modified"].value;
result.Etag = node["Etag"].value;
result.LeaseStatus = LeaseStatusTypeFromString(node["LeaseStatus"].value);
result.LeaseState = LeaseStateTypeFromString(node["LeaseState"].value);
result.LeaseDuration = LeaseDurationTypeFromString(node["LeaseDuration"].value);
result.PublicAccess = PublicAccessTypeFromString(node["PublicAccessType"].value);
result.HasImmutabilityPolicy = node["HasImmutabilityPolicy"].value;
result.HasLegalHold = node["HasLegalHold"].value;
return result;
}

static XmlNode SerializeToXml(const ContainerProperties& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Last-Modified", object.LastModified));
result.AddChildNode(XmlNode("Etag", object.Etag));
result.AddChildNode(XmlNode("LeaseStatus", LeaseStatusTypeToString(object.LeaseStatus)));
result.AddChildNode(XmlNode("LeaseState", LeaseStateTypeToString(object.LeaseState)));
result.AddChildNode(XmlNode("LeaseDuration", LeaseDurationTypeToString(object.LeaseDuration)));
result.AddChildNode(XmlNode("PublicAccessType", PublicAccessTypeToString(object.PublicAccess)));
result.AddChildNode(XmlNode("HasImmutabilityPolicy", object.HasImmutabilityPolicy));
result.AddChildNode(XmlNode("HasLegalHold", object.HasLegalHold));
return result;
}
};  // struct ContainerProperties

// An enumeration of containers
struct ListContainersSegmentResponse
{
std::string ServiceEndpoint;
std::string Prefix;
std::string Marker;
uint32_t MaxResults;
std::vector<ContainerItem> ContainerItems;
std::string NextMarker;

static ListContainersSegmentResponse CreateFromXml(const XmlNode& node)
{
ListContainersSegmentResponse result;
result.ServiceEndpoint = node.getAttribute("ServiceEndpoint");
result.Prefix = node["Prefix"].value;
result.Marker = node["Marker"].value;
result.MaxResults = node["MaxResults"].value;
for (const auto& n : node)
{
result.ContainerItems.push_back(ContainerItem::CreateFromXml(n["Container"]));
}
result.NextMarker = node["NextMarker"].value;
return result;
}

static XmlNode SerializeToXml(const ListContainersSegmentResponse& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Prefix", object.Prefix));
result.AddChildNode(XmlNode("Marker", object.Marker));
result.AddChildNode(XmlNode("MaxResults", object.MaxResults));
result.addChildNode(XmlEmptyArrayNode("ContainerItems"));
for (const auto& item : object.ContainerItems)
{
result["ContainerItems"].AddChildNode(ContainerItem::SerializeToXml(item));
}
result.AddChildNode(XmlNode("NextMarker", object.NextMarker));
return result;
}
};  // struct ListContainersSegmentResponse

// CORS is an HTTP feature that enables a web application running under one domain to access resources in another domain. Web browsers implement a security restriction known as same-origin policy that prevents a web page from calling APIs in a different domain; CORS provides a secure way to allow one domain (the origin domain) to call APIs in another domain
struct CorsRule
{
std::string AllowedOrigins; // The origin domains that are permitted to make a request against the storage service via CORS. The origin domain is the domain from which the request originates. Note that the origin must be an exact case-sensitive match with the origin that the user age sends to the service. You can also use the wildcard character '*' to allow all origin domains to make requests via CORS.
std::string AllowedMethods; // The methods (HTTP request verbs) that the origin domain may use for a CORS request. (comma separated)
std::string AllowedHeaders; // the request headers that the origin domain may specify on the CORS request.
std::string ExposedHeaders; // The response headers that may be sent in the response to the CORS request and exposed by the browser to the request issuer
uint32_t MaxAgeInSeconds; // The maximum amount time that a browser should cache the preflight OPTIONS request.

static XmlNode SerializeToXml(const CorsRule& object)
{
XmlNode result;
result.AddChildNode(XmlNode("AllowedOrigins", object.AllowedOrigins));
result.AddChildNode(XmlNode("AllowedMethods", object.AllowedMethods));
result.AddChildNode(XmlNode("AllowedHeaders", object.AllowedHeaders));
result.AddChildNode(XmlNode("ExposedHeaders", object.ExposedHeaders));
result.AddChildNode(XmlNode("MaxAgeInSeconds", object.MaxAgeInSeconds));
return result;
}
};  // struct CorsRule

// Error codes returned by the service
enum class ErrorCode
{
AccountAlreadyExists,
AccountBeingCreated,
AccountIsDisabled,
AuthenticationFailed,
AuthorizationFailure,
ConditionHeadersNotSupported,
ConditionNotMet,
EmptyMetadataKey,
InsufficientAccountPermissions,
InternalError,
InvalidAuthenticationInfo,
InvalidHeaderValue,
InvalidHttpVerb,
InvalidInput,
InvalidMd5,
InvalidMetadata,
InvalidQueryParameterValue,
InvalidRange,
InvalidResourceName,
InvalidUri,
InvalidXmlDocument,
InvalidXmlNodeValue,
Md5Mismatch,
MetadataTooLarge,
MissingContentLengthHeader,
MissingRequiredQueryParameter,
MissingRequiredHeader,
MissingRequiredXmlNode,
MultipleConditionHeadersNotSupported,
OperationTimedOut,
OutOfRangeInput,
OutOfRangeQueryParameterValue,
RequestBodyTooLarge,
ResourceTypeMismatch,
RequestUrlFailedToParse,
ResourceAlreadyExists,
ResourceNotFound,
ServerBusy,
UnsupportedHeader,
UnsupportedXmlNode,
UnsupportedQueryParameter,
UnsupportedHttpVerb,
AppendPositionConditionNotMet,
BlobAlreadyExists,
BlobNotFound,
BlobOverwritten,
BlobTierInadequateForContentLength,
BlockCountExceedsLimit,
BlockListTooLong,
CannotChangeToLowerTier,
CannotVerifyCopySource,
ContainerAlreadyExists,
ContainerBeingDeleted,
ContainerDisabled,
ContainerNotFound,
ContentLengthLargerThanTierLimit,
CopyAcrossAccountsNotSupported,
CopyIdMismatch,
FeatureVersionMismatch,
IncrementalCopyBlobMismatch,
IncrementalCopyOfEralierVersionSnapshotNotAllowed,
IncrementalCopySourceMustBeSnapshot,
InfiniteLeaseDurationRequired,
InvalidBlobOrBlock,
InvalidBlobTier,
InvalidBlobType,
InvalidBlockId,
InvalidBlockList,
InvalidOperation,
InvalidPageRange,
InvalidSourceBlobType,
InvalidSourceBlobUrl,
InvalidVersionForPageBlobOperation,
LeaseAlreadyPresent,
LeaseAlreadyBroken,
LeaseIdMismatchWithBlobOperation,
LeaseIdMismatchWithContainerOperation,
LeaseIdMismatchWithLeaseOperation,
LeaseIdMissing,
LeaseIsBreakingAndCannotBeAcquired,
LeaseIsBreakingAndCannotBeChanged,
LeaseIsBrokenAndCannotBeRenewed,
LeaseLost,
LeaseNotPresentWithBlobOperation,
LeaseNotPresentWithContainerOperation,
LeaseNotPresentWithLeaseOperation,
MaxBlobSizeConditionNotMet,
NoPendingCopyOperation,
OperationNotAllowedOnIncrementalCopyBlob,
PendingCopyOperation,
PreviousSnapshotCannotBeNewer,
PreviousSnapshotNotFound,
PreviousSnapshotOperationNotSupported,
SequenceNumberConditionNotMet,
SequenceNumberIncrementTooLarge,
SnapshotCountExceeded,
SnaphotOperationRateExceeded,
SnapshotsPresent,
SourceConditionNotMet,
SystemInUse,
TargetConditionNotMet,
UnauthorizedBlobOverwrite,
BlobBeingRehydrated,
BlobArchived,
BlobNotArchived,
AuthorizationSourceIPMismatch,
AuthorizationProtocolMismatch,
AuthorizationPermissionMismatch,
AuthorizationServiceMismatch,
AuthorizationResourceTypeMismatch,
Unknown
};

static std::string ErrorCodeToString(const ErrorCode& errorCode)
{
    switch (errorCode)
    {case ErrorCode::AccountAlreadyExists: return "AccountAlreadyExists";case ErrorCode::AccountBeingCreated: return "AccountBeingCreated";case ErrorCode::AccountIsDisabled: return "AccountIsDisabled";case ErrorCode::AuthenticationFailed: return "AuthenticationFailed";case ErrorCode::AuthorizationFailure: return "AuthorizationFailure";case ErrorCode::ConditionHeadersNotSupported: return "ConditionHeadersNotSupported";case ErrorCode::ConditionNotMet: return "ConditionNotMet";case ErrorCode::EmptyMetadataKey: return "EmptyMetadataKey";case ErrorCode::InsufficientAccountPermissions: return "InsufficientAccountPermissions";case ErrorCode::InternalError: return "InternalError";case ErrorCode::InvalidAuthenticationInfo: return "InvalidAuthenticationInfo";case ErrorCode::InvalidHeaderValue: return "InvalidHeaderValue";case ErrorCode::InvalidHttpVerb: return "InvalidHttpVerb";case ErrorCode::InvalidInput: return "InvalidInput";case ErrorCode::InvalidMd5: return "InvalidMd5";case ErrorCode::InvalidMetadata: return "InvalidMetadata";case ErrorCode::InvalidQueryParameterValue: return "InvalidQueryParameterValue";case ErrorCode::InvalidRange: return "InvalidRange";case ErrorCode::InvalidResourceName: return "InvalidResourceName";case ErrorCode::InvalidUri: return "InvalidUri";case ErrorCode::InvalidXmlDocument: return "InvalidXmlDocument";case ErrorCode::InvalidXmlNodeValue: return "InvalidXmlNodeValue";case ErrorCode::Md5Mismatch: return "Md5Mismatch";case ErrorCode::MetadataTooLarge: return "MetadataTooLarge";case ErrorCode::MissingContentLengthHeader: return "MissingContentLengthHeader";case ErrorCode::MissingRequiredQueryParameter: return "MissingRequiredQueryParameter";case ErrorCode::MissingRequiredHeader: return "MissingRequiredHeader";case ErrorCode::MissingRequiredXmlNode: return "MissingRequiredXmlNode";case ErrorCode::MultipleConditionHeadersNotSupported: return "MultipleConditionHeadersNotSupported";case ErrorCode::OperationTimedOut: return "OperationTimedOut";case ErrorCode::OutOfRangeInput: return "OutOfRangeInput";case ErrorCode::OutOfRangeQueryParameterValue: return "OutOfRangeQueryParameterValue";case ErrorCode::RequestBodyTooLarge: return "RequestBodyTooLarge";case ErrorCode::ResourceTypeMismatch: return "ResourceTypeMismatch";case ErrorCode::RequestUrlFailedToParse: return "RequestUrlFailedToParse";case ErrorCode::ResourceAlreadyExists: return "ResourceAlreadyExists";case ErrorCode::ResourceNotFound: return "ResourceNotFound";case ErrorCode::ServerBusy: return "ServerBusy";case ErrorCode::UnsupportedHeader: return "UnsupportedHeader";case ErrorCode::UnsupportedXmlNode: return "UnsupportedXmlNode";case ErrorCode::UnsupportedQueryParameter: return "UnsupportedQueryParameter";case ErrorCode::UnsupportedHttpVerb: return "UnsupportedHttpVerb";case ErrorCode::AppendPositionConditionNotMet: return "AppendPositionConditionNotMet";case ErrorCode::BlobAlreadyExists: return "BlobAlreadyExists";case ErrorCode::BlobNotFound: return "BlobNotFound";case ErrorCode::BlobOverwritten: return "BlobOverwritten";case ErrorCode::BlobTierInadequateForContentLength: return "BlobTierInadequateForContentLength";case ErrorCode::BlockCountExceedsLimit: return "BlockCountExceedsLimit";case ErrorCode::BlockListTooLong: return "BlockListTooLong";case ErrorCode::CannotChangeToLowerTier: return "CannotChangeToLowerTier";case ErrorCode::CannotVerifyCopySource: return "CannotVerifyCopySource";case ErrorCode::ContainerAlreadyExists: return "ContainerAlreadyExists";case ErrorCode::ContainerBeingDeleted: return "ContainerBeingDeleted";case ErrorCode::ContainerDisabled: return "ContainerDisabled";case ErrorCode::ContainerNotFound: return "ContainerNotFound";case ErrorCode::ContentLengthLargerThanTierLimit: return "ContentLengthLargerThanTierLimit";case ErrorCode::CopyAcrossAccountsNotSupported: return "CopyAcrossAccountsNotSupported";case ErrorCode::CopyIdMismatch: return "CopyIdMismatch";case ErrorCode::FeatureVersionMismatch: return "FeatureVersionMismatch";case ErrorCode::IncrementalCopyBlobMismatch: return "IncrementalCopyBlobMismatch";case ErrorCode::IncrementalCopyOfEralierVersionSnapshotNotAllowed: return "IncrementalCopyOfEralierVersionSnapshotNotAllowed";case ErrorCode::IncrementalCopySourceMustBeSnapshot: return "IncrementalCopySourceMustBeSnapshot";case ErrorCode::InfiniteLeaseDurationRequired: return "InfiniteLeaseDurationRequired";case ErrorCode::InvalidBlobOrBlock: return "InvalidBlobOrBlock";case ErrorCode::InvalidBlobTier: return "InvalidBlobTier";case ErrorCode::InvalidBlobType: return "InvalidBlobType";case ErrorCode::InvalidBlockId: return "InvalidBlockId";case ErrorCode::InvalidBlockList: return "InvalidBlockList";case ErrorCode::InvalidOperation: return "InvalidOperation";case ErrorCode::InvalidPageRange: return "InvalidPageRange";case ErrorCode::InvalidSourceBlobType: return "InvalidSourceBlobType";case ErrorCode::InvalidSourceBlobUrl: return "InvalidSourceBlobUrl";case ErrorCode::InvalidVersionForPageBlobOperation: return "InvalidVersionForPageBlobOperation";case ErrorCode::LeaseAlreadyPresent: return "LeaseAlreadyPresent";case ErrorCode::LeaseAlreadyBroken: return "LeaseAlreadyBroken";case ErrorCode::LeaseIdMismatchWithBlobOperation: return "LeaseIdMismatchWithBlobOperation";case ErrorCode::LeaseIdMismatchWithContainerOperation: return "LeaseIdMismatchWithContainerOperation";case ErrorCode::LeaseIdMismatchWithLeaseOperation: return "LeaseIdMismatchWithLeaseOperation";case ErrorCode::LeaseIdMissing: return "LeaseIdMissing";case ErrorCode::LeaseIsBreakingAndCannotBeAcquired: return "LeaseIsBreakingAndCannotBeAcquired";case ErrorCode::LeaseIsBreakingAndCannotBeChanged: return "LeaseIsBreakingAndCannotBeChanged";case ErrorCode::LeaseIsBrokenAndCannotBeRenewed: return "LeaseIsBrokenAndCannotBeRenewed";case ErrorCode::LeaseLost: return "LeaseLost";case ErrorCode::LeaseNotPresentWithBlobOperation: return "LeaseNotPresentWithBlobOperation";case ErrorCode::LeaseNotPresentWithContainerOperation: return "LeaseNotPresentWithContainerOperation";case ErrorCode::LeaseNotPresentWithLeaseOperation: return "LeaseNotPresentWithLeaseOperation";case ErrorCode::MaxBlobSizeConditionNotMet: return "MaxBlobSizeConditionNotMet";case ErrorCode::NoPendingCopyOperation: return "NoPendingCopyOperation";case ErrorCode::OperationNotAllowedOnIncrementalCopyBlob: return "OperationNotAllowedOnIncrementalCopyBlob";case ErrorCode::PendingCopyOperation: return "PendingCopyOperation";case ErrorCode::PreviousSnapshotCannotBeNewer: return "PreviousSnapshotCannotBeNewer";case ErrorCode::PreviousSnapshotNotFound: return "PreviousSnapshotNotFound";case ErrorCode::PreviousSnapshotOperationNotSupported: return "PreviousSnapshotOperationNotSupported";case ErrorCode::SequenceNumberConditionNotMet: return "SequenceNumberConditionNotMet";case ErrorCode::SequenceNumberIncrementTooLarge: return "SequenceNumberIncrementTooLarge";case ErrorCode::SnapshotCountExceeded: return "SnapshotCountExceeded";case ErrorCode::SnaphotOperationRateExceeded: return "SnaphotOperationRateExceeded";case ErrorCode::SnapshotsPresent: return "SnapshotsPresent";case ErrorCode::SourceConditionNotMet: return "SourceConditionNotMet";case ErrorCode::SystemInUse: return "SystemInUse";case ErrorCode::TargetConditionNotMet: return "TargetConditionNotMet";case ErrorCode::UnauthorizedBlobOverwrite: return "UnauthorizedBlobOverwrite";case ErrorCode::BlobBeingRehydrated: return "BlobBeingRehydrated";case ErrorCode::BlobArchived: return "BlobArchived";case ErrorCode::BlobNotArchived: return "BlobNotArchived";case ErrorCode::AuthorizationSourceIPMismatch: return "AuthorizationSourceIPMismatch";case ErrorCode::AuthorizationProtocolMismatch: return "AuthorizationProtocolMismatch";case ErrorCode::AuthorizationPermissionMismatch: return "AuthorizationPermissionMismatch";case ErrorCode::AuthorizationServiceMismatch: return "AuthorizationServiceMismatch";case ErrorCode::AuthorizationResourceTypeMismatch: return "AuthorizationResourceTypeMismatch";default: return std::string(); }}

static ErrorCode ErrorCodeFromString(const std::string& errorCode)
{if (errorCode == "AccountAlreadyExists") { return ErrorCode::AccountAlreadyExists; }if (errorCode == "AccountBeingCreated") { return ErrorCode::AccountBeingCreated; }if (errorCode == "AccountIsDisabled") { return ErrorCode::AccountIsDisabled; }if (errorCode == "AuthenticationFailed") { return ErrorCode::AuthenticationFailed; }if (errorCode == "AuthorizationFailure") { return ErrorCode::AuthorizationFailure; }if (errorCode == "ConditionHeadersNotSupported") { return ErrorCode::ConditionHeadersNotSupported; }if (errorCode == "ConditionNotMet") { return ErrorCode::ConditionNotMet; }if (errorCode == "EmptyMetadataKey") { return ErrorCode::EmptyMetadataKey; }if (errorCode == "InsufficientAccountPermissions") { return ErrorCode::InsufficientAccountPermissions; }if (errorCode == "InternalError") { return ErrorCode::InternalError; }if (errorCode == "InvalidAuthenticationInfo") { return ErrorCode::InvalidAuthenticationInfo; }if (errorCode == "InvalidHeaderValue") { return ErrorCode::InvalidHeaderValue; }if (errorCode == "InvalidHttpVerb") { return ErrorCode::InvalidHttpVerb; }if (errorCode == "InvalidInput") { return ErrorCode::InvalidInput; }if (errorCode == "InvalidMd5") { return ErrorCode::InvalidMd5; }if (errorCode == "InvalidMetadata") { return ErrorCode::InvalidMetadata; }if (errorCode == "InvalidQueryParameterValue") { return ErrorCode::InvalidQueryParameterValue; }if (errorCode == "InvalidRange") { return ErrorCode::InvalidRange; }if (errorCode == "InvalidResourceName") { return ErrorCode::InvalidResourceName; }if (errorCode == "InvalidUri") { return ErrorCode::InvalidUri; }if (errorCode == "InvalidXmlDocument") { return ErrorCode::InvalidXmlDocument; }if (errorCode == "InvalidXmlNodeValue") { return ErrorCode::InvalidXmlNodeValue; }if (errorCode == "Md5Mismatch") { return ErrorCode::Md5Mismatch; }if (errorCode == "MetadataTooLarge") { return ErrorCode::MetadataTooLarge; }if (errorCode == "MissingContentLengthHeader") { return ErrorCode::MissingContentLengthHeader; }if (errorCode == "MissingRequiredQueryParameter") { return ErrorCode::MissingRequiredQueryParameter; }if (errorCode == "MissingRequiredHeader") { return ErrorCode::MissingRequiredHeader; }if (errorCode == "MissingRequiredXmlNode") { return ErrorCode::MissingRequiredXmlNode; }if (errorCode == "MultipleConditionHeadersNotSupported") { return ErrorCode::MultipleConditionHeadersNotSupported; }if (errorCode == "OperationTimedOut") { return ErrorCode::OperationTimedOut; }if (errorCode == "OutOfRangeInput") { return ErrorCode::OutOfRangeInput; }if (errorCode == "OutOfRangeQueryParameterValue") { return ErrorCode::OutOfRangeQueryParameterValue; }if (errorCode == "RequestBodyTooLarge") { return ErrorCode::RequestBodyTooLarge; }if (errorCode == "ResourceTypeMismatch") { return ErrorCode::ResourceTypeMismatch; }if (errorCode == "RequestUrlFailedToParse") { return ErrorCode::RequestUrlFailedToParse; }if (errorCode == "ResourceAlreadyExists") { return ErrorCode::ResourceAlreadyExists; }if (errorCode == "ResourceNotFound") { return ErrorCode::ResourceNotFound; }if (errorCode == "ServerBusy") { return ErrorCode::ServerBusy; }if (errorCode == "UnsupportedHeader") { return ErrorCode::UnsupportedHeader; }if (errorCode == "UnsupportedXmlNode") { return ErrorCode::UnsupportedXmlNode; }if (errorCode == "UnsupportedQueryParameter") { return ErrorCode::UnsupportedQueryParameter; }if (errorCode == "UnsupportedHttpVerb") { return ErrorCode::UnsupportedHttpVerb; }if (errorCode == "AppendPositionConditionNotMet") { return ErrorCode::AppendPositionConditionNotMet; }if (errorCode == "BlobAlreadyExists") { return ErrorCode::BlobAlreadyExists; }if (errorCode == "BlobNotFound") { return ErrorCode::BlobNotFound; }if (errorCode == "BlobOverwritten") { return ErrorCode::BlobOverwritten; }if (errorCode == "BlobTierInadequateForContentLength") { return ErrorCode::BlobTierInadequateForContentLength; }if (errorCode == "BlockCountExceedsLimit") { return ErrorCode::BlockCountExceedsLimit; }if (errorCode == "BlockListTooLong") { return ErrorCode::BlockListTooLong; }if (errorCode == "CannotChangeToLowerTier") { return ErrorCode::CannotChangeToLowerTier; }if (errorCode == "CannotVerifyCopySource") { return ErrorCode::CannotVerifyCopySource; }if (errorCode == "ContainerAlreadyExists") { return ErrorCode::ContainerAlreadyExists; }if (errorCode == "ContainerBeingDeleted") { return ErrorCode::ContainerBeingDeleted; }if (errorCode == "ContainerDisabled") { return ErrorCode::ContainerDisabled; }if (errorCode == "ContainerNotFound") { return ErrorCode::ContainerNotFound; }if (errorCode == "ContentLengthLargerThanTierLimit") { return ErrorCode::ContentLengthLargerThanTierLimit; }if (errorCode == "CopyAcrossAccountsNotSupported") { return ErrorCode::CopyAcrossAccountsNotSupported; }if (errorCode == "CopyIdMismatch") { return ErrorCode::CopyIdMismatch; }if (errorCode == "FeatureVersionMismatch") { return ErrorCode::FeatureVersionMismatch; }if (errorCode == "IncrementalCopyBlobMismatch") { return ErrorCode::IncrementalCopyBlobMismatch; }if (errorCode == "IncrementalCopyOfEralierVersionSnapshotNotAllowed") { return ErrorCode::IncrementalCopyOfEralierVersionSnapshotNotAllowed; }if (errorCode == "IncrementalCopySourceMustBeSnapshot") { return ErrorCode::IncrementalCopySourceMustBeSnapshot; }if (errorCode == "InfiniteLeaseDurationRequired") { return ErrorCode::InfiniteLeaseDurationRequired; }if (errorCode == "InvalidBlobOrBlock") { return ErrorCode::InvalidBlobOrBlock; }if (errorCode == "InvalidBlobTier") { return ErrorCode::InvalidBlobTier; }if (errorCode == "InvalidBlobType") { return ErrorCode::InvalidBlobType; }if (errorCode == "InvalidBlockId") { return ErrorCode::InvalidBlockId; }if (errorCode == "InvalidBlockList") { return ErrorCode::InvalidBlockList; }if (errorCode == "InvalidOperation") { return ErrorCode::InvalidOperation; }if (errorCode == "InvalidPageRange") { return ErrorCode::InvalidPageRange; }if (errorCode == "InvalidSourceBlobType") { return ErrorCode::InvalidSourceBlobType; }if (errorCode == "InvalidSourceBlobUrl") { return ErrorCode::InvalidSourceBlobUrl; }if (errorCode == "InvalidVersionForPageBlobOperation") { return ErrorCode::InvalidVersionForPageBlobOperation; }if (errorCode == "LeaseAlreadyPresent") { return ErrorCode::LeaseAlreadyPresent; }if (errorCode == "LeaseAlreadyBroken") { return ErrorCode::LeaseAlreadyBroken; }if (errorCode == "LeaseIdMismatchWithBlobOperation") { return ErrorCode::LeaseIdMismatchWithBlobOperation; }if (errorCode == "LeaseIdMismatchWithContainerOperation") { return ErrorCode::LeaseIdMismatchWithContainerOperation; }if (errorCode == "LeaseIdMismatchWithLeaseOperation") { return ErrorCode::LeaseIdMismatchWithLeaseOperation; }if (errorCode == "LeaseIdMissing") { return ErrorCode::LeaseIdMissing; }if (errorCode == "LeaseIsBreakingAndCannotBeAcquired") { return ErrorCode::LeaseIsBreakingAndCannotBeAcquired; }if (errorCode == "LeaseIsBreakingAndCannotBeChanged") { return ErrorCode::LeaseIsBreakingAndCannotBeChanged; }if (errorCode == "LeaseIsBrokenAndCannotBeRenewed") { return ErrorCode::LeaseIsBrokenAndCannotBeRenewed; }if (errorCode == "LeaseLost") { return ErrorCode::LeaseLost; }if (errorCode == "LeaseNotPresentWithBlobOperation") { return ErrorCode::LeaseNotPresentWithBlobOperation; }if (errorCode == "LeaseNotPresentWithContainerOperation") { return ErrorCode::LeaseNotPresentWithContainerOperation; }if (errorCode == "LeaseNotPresentWithLeaseOperation") { return ErrorCode::LeaseNotPresentWithLeaseOperation; }if (errorCode == "MaxBlobSizeConditionNotMet") { return ErrorCode::MaxBlobSizeConditionNotMet; }if (errorCode == "NoPendingCopyOperation") { return ErrorCode::NoPendingCopyOperation; }if (errorCode == "OperationNotAllowedOnIncrementalCopyBlob") { return ErrorCode::OperationNotAllowedOnIncrementalCopyBlob; }if (errorCode == "PendingCopyOperation") { return ErrorCode::PendingCopyOperation; }if (errorCode == "PreviousSnapshotCannotBeNewer") { return ErrorCode::PreviousSnapshotCannotBeNewer; }if (errorCode == "PreviousSnapshotNotFound") { return ErrorCode::PreviousSnapshotNotFound; }if (errorCode == "PreviousSnapshotOperationNotSupported") { return ErrorCode::PreviousSnapshotOperationNotSupported; }if (errorCode == "SequenceNumberConditionNotMet") { return ErrorCode::SequenceNumberConditionNotMet; }if (errorCode == "SequenceNumberIncrementTooLarge") { return ErrorCode::SequenceNumberIncrementTooLarge; }if (errorCode == "SnapshotCountExceeded") { return ErrorCode::SnapshotCountExceeded; }if (errorCode == "SnaphotOperationRateExceeded") { return ErrorCode::SnaphotOperationRateExceeded; }if (errorCode == "SnapshotsPresent") { return ErrorCode::SnapshotsPresent; }if (errorCode == "SourceConditionNotMet") { return ErrorCode::SourceConditionNotMet; }if (errorCode == "SystemInUse") { return ErrorCode::SystemInUse; }if (errorCode == "TargetConditionNotMet") { return ErrorCode::TargetConditionNotMet; }if (errorCode == "UnauthorizedBlobOverwrite") { return ErrorCode::UnauthorizedBlobOverwrite; }if (errorCode == "BlobBeingRehydrated") { return ErrorCode::BlobBeingRehydrated; }if (errorCode == "BlobArchived") { return ErrorCode::BlobArchived; }if (errorCode == "BlobNotArchived") { return ErrorCode::BlobNotArchived; }if (errorCode == "AuthorizationSourceIPMismatch") { return ErrorCode::AuthorizationSourceIPMismatch; }if (errorCode == "AuthorizationProtocolMismatch") { return ErrorCode::AuthorizationProtocolMismatch; }if (errorCode == "AuthorizationPermissionMismatch") { return ErrorCode::AuthorizationPermissionMismatch; }if (errorCode == "AuthorizationServiceMismatch") { return ErrorCode::AuthorizationServiceMismatch; }if (errorCode == "AuthorizationResourceTypeMismatch") { return ErrorCode::AuthorizationResourceTypeMismatch; }throw std::runtime_error("Cannot convert " + errorCode + " to ErrorCode");};  // enum class ErrorCode

// Geo-Replication information for the Secondary Storage Service
struct GeoReplication
{
std::string Status; // The status of the secondary location
std::string LastSyncTime; // A GMT date/time value, to the second. All primary writes preceding this value are guaranteed to be available for read operations at the secondary. Primary writes after this point in time may or may not be available for reads.

static XmlNode SerializeToXml(const GeoReplication& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Status", object.Status));
result.AddChildNode(XmlNode("LastSyncTime", object.LastSyncTime));
return result;
}
};  // struct GeoReplication

// Azure Analytics Logging settings.
struct Logging
{
std::string Version; // The version of Storage Analytics to configure.
bool Delete; // Indicates whether all delete requests should be logged.
bool Read; // Indicates whether all read requests should be logged.
bool Write; // Indicates whether all write requests should be logged.
RetentionPolicy RetentionPolicy;

static XmlNode SerializeToXml(const Logging& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Version", object.Version));
result.AddChildNode(XmlNode("Delete", object.Delete));
result.AddChildNode(XmlNode("Read", object.Read));
result.AddChildNode(XmlNode("Write", object.Write));
result.AddChildNode(RetentionPolicy::SerializeToXml(object.RetentionPolicy));
return result;
}
};  // struct Logging

typedef std::map<std::string, std::string> ContainerMetadata;

typedef std::map<std::string, std::string> BlobMetadata;

// a summary of request statistics grouped by API in hour or minute aggregates for blobs
struct Metrics
{
std::string Version; // The version of Storage Analytics to configure.
bool Enabled; // Indicates whether metrics are enabled for the Blob service.
bool IncludeAPIs; // Indicates whether metrics should generate summary statistics for called API operations.
RetentionPolicy RetentionPolicy;

static XmlNode SerializeToXml(const Metrics& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Version", object.Version));
result.AddChildNode(XmlNode("Enabled", object.Enabled));
result.AddChildNode(XmlNode("IncludeAPIs", object.IncludeAPIs));
result.AddChildNode(RetentionPolicy::SerializeToXml(object.RetentionPolicy));
return result;
}
};  // struct Metrics

// the list of pages
struct PageList
{
std::vector<PageRange> PageRange;
std::vector<ClearRange> ClearRange;

static PageList CreateFromXml(const XmlNode& node)
{
PageList result;
for (const auto& n : node)
{
result.PageRange.push_back(PageRange::CreateFromXml(n["PageRange"]));
}
for (const auto& n : node)
{
result.ClearRange.push_back(ClearRange::CreateFromXml(n["ClearRange"]));
}
return result;
}

static XmlNode SerializeToXml(const PageList& object)
{
XmlNode result;
result.addChildNode(XmlEmptyArrayNode("PageRange"));
for (const auto& item : object.PageRange)
{
result["PageRange"].AddChildNode(PageRange::SerializeToXml(item));
}
result.addChildNode(XmlEmptyArrayNode("ClearRange"));
for (const auto& item : object.ClearRange)
{
result["ClearRange"].AddChildNode(ClearRange::SerializeToXml(item));
}
return result;
}
};  // struct PageList

struct PageRange
{
uint32_t Start;
uint32_t End;

static PageRange CreateFromXml(const XmlNode& node)
{
PageRange result;
result.Start = node["Start"].value;
result.End = node["End"].value;
return result;
}

static XmlNode SerializeToXml(const PageRange& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Start", object.Start));
result.AddChildNode(XmlNode("End", object.End));
return result;
}
};  // struct PageRange

struct ClearRange
{
uint32_t Start;
uint32_t End;

static ClearRange CreateFromXml(const XmlNode& node)
{
ClearRange result;
result.Start = node["Start"].value;
result.End = node["End"].value;
return result;
}

static XmlNode SerializeToXml(const ClearRange& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Start", object.Start));
result.AddChildNode(XmlNode("End", object.End));
return result;
}
};  // struct ClearRange

// the retention policy which determines how long the associated data should persist
struct RetentionPolicy
{
bool Enabled; // Indicates whether a retention policy is enabled for the storage service
uint32_t Days; // Indicates the number of days that metrics or logging or soft-deleted data should be retained. All data older than this value will be deleted

static XmlNode SerializeToXml(const RetentionPolicy& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Enabled", object.Enabled));
result.AddChildNode(XmlNode("Days", object.Days));
return result;
}
};  // struct RetentionPolicy

// signed identifier
struct SignedIdentifier
{
std::string Id; // a unique id
AccessPolicy AccessPolicy;

static SignedIdentifier CreateFromXml(const XmlNode& node)
{
SignedIdentifier result;
result.Id = node["Id"].value;
result.AccessPolicy = AccessPolicy::CreateFromXml(node["AccessPolicy"]);
return result;
}

static XmlNode SerializeToXml(const SignedIdentifier& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Id", object.Id));
result.AddChildNode(AccessPolicy::SerializeToXml(object.AccessPolicy));
return result;
}
};  // struct SignedIdentifier

// The properties that enable an account to host a static website
struct StaticWebsite
{
bool Enabled; // Indicates whether this account is hosting a static website
std::string IndexDocument; // The default name of the index page under each directory
std::string ErrorDocument404Path; // The absolute path of the custom 404 page

static XmlNode SerializeToXml(const StaticWebsite& object)
{
XmlNode result;
result.AddChildNode(XmlNode("Enabled", object.Enabled));
result.AddChildNode(XmlNode("IndexDocument", object.IndexDocument));
result.AddChildNode(XmlNode("ErrorDocument404Path", object.ErrorDocument404Path));
return result;
}
};  // struct StaticWebsite

// Storage Service Properties.
struct StorageServiceProperties
{
Logging Logging;
Metrics HourMetrics;
Metrics MinuteMetrics;
std::vector<CorsRule> Cors; // The set of CORS rules.
std::string DefaultServiceVersion; // The default version to use for requests to the Blob service if an incoming request's version is not specified. Possible values include version 2008-10-27 and all more recent versions
RetentionPolicy DeleteRetentionPolicy;
StaticWebsite StaticWebsite;

static XmlNode SerializeToXml(const StorageServiceProperties& object)
{
XmlNode result;
result.AddChildNode(Logging::SerializeToXml(object.Logging));
result.AddChildNode(Metrics::SerializeToXml(object.HourMetrics));
result.AddChildNode(Metrics::SerializeToXml(object.MinuteMetrics));
result.addChildNode(XmlEmptyArrayNode("Cors"));
for (const auto& item : object.Cors)
{
result["Cors"].AddChildNode(CorsRule::SerializeToXml(item));
}
result.AddChildNode(XmlNode("DefaultServiceVersion", object.DefaultServiceVersion));
result.AddChildNode(RetentionPolicy::SerializeToXml(object.DeleteRetentionPolicy));
result.AddChildNode(StaticWebsite::SerializeToXml(object.StaticWebsite));
return result;
}
};  // struct StorageServiceProperties

// Stats for the storage service.
struct StorageServiceStats
{
GeoReplication GeoReplication;

static XmlNode SerializeToXml(const StorageServiceStats& object)
{
XmlNode result;
result.AddChildNode(GeoReplication::SerializeToXml(object.GeoReplication));
return result;
}
};  // struct StorageServiceStats


struct ServiceSetPropertiesOptions
{
StorageServiceProperties StorageServiceProperties; // The StorageService properties.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceSetPropertiesCreateRequest(std::string url, const ServiceSetPropertiesOptions& serviceSetPropertiesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(restype, service);
request.addQueryParameter(comp, properties);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceSetPropertiesResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
};

static ServiceSetPropertiesResponse ServiceSetPropertiesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceSetPropertiesResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// Success (Accepted)
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceSetProperties(std::string url, const ServiceSetPropertiesOptions& serviceSetPropertiesOptions)
{
return ServiceSetPropertiesParseResponse(Azure::Core::Http::Client::Send(ServiceSetPropertiesCreateRequest(url, serviceSetPropertiesOptions)));
};

struct ServiceGetPropertiesOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceGetPropertiesCreateRequest(std::string url, const ServiceGetPropertiesOptions& serviceGetPropertiesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, service);
request.addQueryParameter(comp, properties);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceGetPropertiesResponse
{
StorageServiceProperties StorageServiceProperties;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
};

static ServiceGetPropertiesResponse ServiceGetPropertiesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceGetPropertiesResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.StorageServiceProperties = StorageServiceProperties::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceGetProperties(std::string url, const ServiceGetPropertiesOptions& serviceGetPropertiesOptions)
{
return ServiceGetPropertiesParseResponse(Azure::Core::Http::Client::Send(ServiceGetPropertiesCreateRequest(url, serviceGetPropertiesOptions)));
};

struct ServiceGetStatisticsOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceGetStatisticsCreateRequest(std::string url, const ServiceGetStatisticsOptions& serviceGetStatisticsOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, service);
request.addQueryParameter(comp, stats);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceGetStatisticsResponse
{
StorageServiceStats StorageServiceStats;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ServiceGetStatisticsResponse ServiceGetStatisticsParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceGetStatisticsResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.StorageServiceStats = StorageServiceStats::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceGetStatistics(std::string url, const ServiceGetStatisticsOptions& serviceGetStatisticsOptions)
{
return ServiceGetStatisticsParseResponse(Azure::Core::Http::Client::Send(ServiceGetStatisticsCreateRequest(url, serviceGetStatisticsOptions)));
};

struct ServiceListContainersSegmentOptions
{
std::string Prefix = std::string(); // Filters the results to return only containers whose name begins with the specified prefix.
std::string Marker = std::string(); // A string value that identifies the portion of the list of containers to be returned with the next listing operation. The operation returns the NextMarker value within the response body if the listing operation did not return all containers remaining to be listed with the current page. The NextMarker value can be used as the value for the marker parameter in a subsequent call to request the next page of list items. The marker value is opaque to the client.
uint32_t MaxResults = uint32_t(); // Specifies the maximum number of containers to return. If the request does not specify maxresults, or specifies a value greater than 5000, the server will return up to 5000 items. Note that if the listing operation crosses a partition boundary, then the service will return a continuation token for retrieving the remainder of the results. For this reason, it is possible that the service will return fewer results than specified by maxresults, or than the default of 5000.
std::string ListContainersInclude = std::string(); // Include this parameter to specify that the container's metadata be returned as part of the response body.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceListContainersSegmentCreateRequest(std::string url, const ServiceListContainersSegmentOptions& serviceListContainersSegmentOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(comp, list);
if (!options.Prefix.empty())
{
    request.addHeader(k_QueryPrefix, options.Prefix);
}if (!options.Marker.empty())
{
    request.addHeader(k_QueryMarker, options.Marker);
}if (!std::to_string(options.MaxResults).empty())
{
    request.addHeader(k_QueryMaxResults, std::to_string(options.MaxResults));
}if (!options.ListContainersInclude.empty())
{
    request.addHeader(k_QueryListContainersInclude, options.ListContainersInclude);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceListContainersSegmentResponse
{
ListContainersSegmentResponse ListContainersSegmentResponse;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
};

static ServiceListContainersSegmentResponse ServiceListContainersSegmentParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceListContainersSegmentResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.ListContainersSegmentResponse = ListContainersSegmentResponse::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceListContainersSegment(std::string url, const ServiceListContainersSegmentOptions& serviceListContainersSegmentOptions)
{
return ServiceListContainersSegmentParseResponse(Azure::Core::Http::Client::Send(ServiceListContainersSegmentCreateRequest(url, serviceListContainersSegmentOptions)));
};

struct ServiceGetUserDelegationKeyOptions
{
KeyInfo KeyInfo; // None
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceGetUserDelegationKeyCreateRequest(std::string url, const ServiceGetUserDelegationKeyOptions& serviceGetUserDelegationKeyOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::post, url);
request.addQueryParameter(restype, service);
request.addQueryParameter(comp, userdelegationkey);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceGetUserDelegationKeyResponse
{
UserDelegationKey UserDelegationKey;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ServiceGetUserDelegationKeyResponse ServiceGetUserDelegationKeyParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceGetUserDelegationKeyResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.UserDelegationKey = UserDelegationKey::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceGetUserDelegationKey(std::string url, const ServiceGetUserDelegationKeyOptions& serviceGetUserDelegationKeyOptions)
{
return ServiceGetUserDelegationKeyParseResponse(Azure::Core::Http::Client::Send(ServiceGetUserDelegationKeyCreateRequest(url, serviceGetUserDelegationKeyOptions)));
};

struct ServiceGetAccountInfoOptions
{
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request ServiceGetAccountInfoCreateRequest(std::string url, const ServiceGetAccountInfoOptions& serviceGetAccountInfoOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, account);
request.addQueryParameter(comp, properties);
request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct ServiceGetAccountInfoResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string SkuName;
std::string AccountKind;
};

static ServiceGetAccountInfoResponse ServiceGetAccountInfoParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceGetAccountInfoResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success (OK)
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.SkuName = response.getHeaders().get("x-ms-sku-name");
result.AccountKind = response.getHeaders().get("x-ms-account-kind");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceGetAccountInfo(std::string url, const ServiceGetAccountInfoOptions& serviceGetAccountInfoOptions)
{
return ServiceGetAccountInfoParseResponse(Azure::Core::Http::Client::Send(ServiceGetAccountInfoCreateRequest(url, serviceGetAccountInfoOptions)));
};

struct ServiceSubmitBatchOptions
{
Azure::Core::Http::BodyBuffer* Body; // Initial data
uint32_t ContentLength; // The length of the request.
std::string MultipartContentType; // Required. The value of this header must be multipart/mixed with a batch boundary. Example header value: multipart/mixed; boundary=batch_<GUID>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ServiceSubmitBatchCreateRequest(std::string url, const ServiceSubmitBatchOptions& serviceSubmitBatchOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::post, url);
request.addQueryParameter(comp, batch);
request.setBodyBuffer(options.Body);
request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
request.addHeader(k_HeaderMultipartContentType, options.MultipartContentType);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ServiceSubmitBatchResponse
{
Azure::Core::Http::BodyBuffer BodyBuffer;
std::string ContentType;
std::string RequestId;
std::string Version;
};

static ServiceSubmitBatchResponse ServiceSubmitBatchParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ServiceSubmitBatchResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.BodyBuffer = response.getBodyBuffer();
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ServiceSubmitBatch(std::string url, const ServiceSubmitBatchOptions& serviceSubmitBatchOptions)
{
return ServiceSubmitBatchParseResponse(Azure::Core::Http::Client::Send(ServiceSubmitBatchCreateRequest(url, serviceSubmitBatchOptions)));
};

struct ContainerCreateOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string BlobPublicAccess = std::string(); // Specifies whether data in the container may be accessed publicly and the level of access
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerCreateCreateRequest(std::string url, const ContainerCreateOptions& containerCreateOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(restype, container);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.BlobPublicAccess.empty())
{
    request.addHeader(k_HeaderBlobPublicAccess, options.BlobPublicAccess);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerCreateResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerCreateResponse ContainerCreateParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerCreateResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// Success, Container created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerCreate(std::string url, const ContainerCreateOptions& containerCreateOptions)
{
return ContainerCreateParseResponse(Azure::Core::Http::Client::Send(ContainerCreateCreateRequest(url, containerCreateOptions)));
};

struct ContainerGetPropertiesOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerGetPropertiesCreateRequest(std::string url, const ContainerGetPropertiesOptions& containerGetPropertiesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, container);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerGetPropertiesResponse
{
std::string Metadata;
std::string ETag;
std::string LastModified;
std::string LeaseDuration;
std::string LeaseState;
std::string LeaseStatus;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string BlobPublicAccess;
bool HasImmutabilityPolicy;
bool HasLegalHold;
};

static ContainerGetPropertiesResponse ContainerGetPropertiesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerGetPropertiesResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success
result.Metadata = response.getHeaders().get(k_HeaderMetadata);
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseDuration = response.getHeaders().get(k_HeaderLeaseDuration);
result.LeaseState = response.getHeaders().get("x-ms-lease-state");
result.LeaseStatus = response.getHeaders().get("x-ms-lease-status");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.BlobPublicAccess = response.getHeaders().get(k_HeaderBlobPublicAccess);
result.HasImmutabilityPolicy = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-has-immutability-policy")));
result.HasLegalHold = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-has-legal-hold")));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerGetProperties(std::string url, const ContainerGetPropertiesOptions& containerGetPropertiesOptions)
{
return ContainerGetPropertiesParseResponse(Azure::Core::Http::Client::Send(ContainerGetPropertiesCreateRequest(url, containerGetPropertiesOptions)));
};

struct ContainerDeleteOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerDeleteCreateRequest(std::string url, const ContainerDeleteOptions& containerDeleteOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::delete, url);
request.addQueryParameter(restype, container);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerDeleteResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerDeleteResponse ContainerDeleteParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerDeleteResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// Accepted
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerDelete(std::string url, const ContainerDeleteOptions& containerDeleteOptions)
{
return ContainerDeleteParseResponse(Azure::Core::Http::Client::Send(ContainerDeleteCreateRequest(url, containerDeleteOptions)));
};

struct ContainerSetMetadataOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerSetMetadataCreateRequest(std::string url, const ContainerSetMetadataOptions& containerSetMetadataOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(restype, container);
request.addQueryParameter(comp, metadata);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerSetMetadataResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerSetMetadataResponse ContainerSetMetadataParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerSetMetadataResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerSetMetadata(std::string url, const ContainerSetMetadataOptions& containerSetMetadataOptions)
{
return ContainerSetMetadataParseResponse(Azure::Core::Http::Client::Send(ContainerSetMetadataCreateRequest(url, containerSetMetadataOptions)));
};

struct ContainerGetAccessPolicyOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerGetAccessPolicyCreateRequest(std::string url, const ContainerGetAccessPolicyOptions& containerGetAccessPolicyOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, container);
request.addQueryParameter(comp, acl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerGetAccessPolicyResponse
{
SignedIdentifiers SignedIdentifiers;
std::string BlobPublicAccess;
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerGetAccessPolicyResponse ContainerGetAccessPolicyParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerGetAccessPolicyResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success
result.BlobPublicAccess = response.getHeaders().get(k_HeaderBlobPublicAccess);
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.SignedIdentifiers = SignedIdentifiers::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerGetAccessPolicy(std::string url, const ContainerGetAccessPolicyOptions& containerGetAccessPolicyOptions)
{
return ContainerGetAccessPolicyParseResponse(Azure::Core::Http::Client::Send(ContainerGetAccessPolicyCreateRequest(url, containerGetAccessPolicyOptions)));
};

struct ContainerSetAccessPolicyOptions
{
ContainerAcl ContainerAcl = ContainerAcl(); // the acls for the container
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string BlobPublicAccess = std::string(); // Specifies whether data in the container may be accessed publicly and the level of access
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerSetAccessPolicyCreateRequest(std::string url, const ContainerSetAccessPolicyOptions& containerSetAccessPolicyOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(restype, container);
request.addQueryParameter(comp, acl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.BlobPublicAccess.empty())
{
    request.addHeader(k_HeaderBlobPublicAccess, options.BlobPublicAccess);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerSetAccessPolicyResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerSetAccessPolicyResponse ContainerSetAccessPolicyParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerSetAccessPolicyResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerSetAccessPolicy(std::string url, const ContainerSetAccessPolicyOptions& containerSetAccessPolicyOptions)
{
return ContainerSetAccessPolicyParseResponse(Azure::Core::Http::Client::Send(ContainerSetAccessPolicyCreateRequest(url, containerSetAccessPolicyOptions)));
};

struct ContainerAcquireLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t LeaseDuration = uint32_t(); // Specifies the duration of the lease, in seconds, or negative one (-1) for a lease that never expires. A non-infinite lease can be between 15 and 60 seconds. A lease duration cannot be changed using renew or change.
std::string ProposedLeaseIdOptional = std::string(); // Proposed lease ID, in a GUID string format. The Blob service returns 400 (Invalid request) if the proposed lease ID is not in the correct format. See Guid Constructor (String) for a list of valid GUID string formats.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerAcquireLeaseCreateRequest(std::string url, const ContainerAcquireLeaseOptions& containerAcquireLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(restype, container);
request.addQueryParameter(x-ms-lease-action, acquire);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.LeaseDuration).empty())
{
    request.addHeader(k_HeaderLeaseDuration, std::to_string(options.LeaseDuration));
}if (!options.ProposedLeaseIdOptional.empty())
{
    request.addHeader(k_HeaderProposedLeaseIdOptional, options.ProposedLeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerAcquireLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string LeaseId;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerAcquireLeaseResponse ContainerAcquireLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerAcquireLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The Acquire operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerAcquireLease(std::string url, const ContainerAcquireLeaseOptions& containerAcquireLeaseOptions)
{
return ContainerAcquireLeaseParseResponse(Azure::Core::Http::Client::Send(ContainerAcquireLeaseCreateRequest(url, containerAcquireLeaseOptions)));
};

struct ContainerReleaseLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerReleaseLeaseCreateRequest(std::string url, const ContainerReleaseLeaseOptions& containerReleaseLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(restype, container);
request.addQueryParameter(x-ms-lease-action, release);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerReleaseLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerReleaseLeaseResponse ContainerReleaseLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerReleaseLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Release operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerReleaseLease(std::string url, const ContainerReleaseLeaseOptions& containerReleaseLeaseOptions)
{
return ContainerReleaseLeaseParseResponse(Azure::Core::Http::Client::Send(ContainerReleaseLeaseCreateRequest(url, containerReleaseLeaseOptions)));
};

struct ContainerRenewLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerRenewLeaseCreateRequest(std::string url, const ContainerRenewLeaseOptions& containerRenewLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(restype, container);
request.addQueryParameter(x-ms-lease-action, renew);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerRenewLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string LeaseId;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerRenewLeaseResponse ContainerRenewLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerRenewLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Renew operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerRenewLease(std::string url, const ContainerRenewLeaseOptions& containerRenewLeaseOptions)
{
return ContainerRenewLeaseParseResponse(Azure::Core::Http::Client::Send(ContainerRenewLeaseCreateRequest(url, containerRenewLeaseOptions)));
};

struct ContainerBreakLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t LeaseBreakPeriod = uint32_t(); // For a break operation, proposed duration the lease should continue before it is broken, in seconds, between 0 and 60. This break period is only used if it is shorter than the time remaining on the lease. If longer, the time remaining on the lease is used. A new lease will not be available before the break period has expired, but the lease may be held for longer than the break period. If this header does not appear with a break operation, a fixed-duration lease breaks after the remaining lease period elapses, and an infinite lease breaks immediately.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerBreakLeaseCreateRequest(std::string url, const ContainerBreakLeaseOptions& containerBreakLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(restype, container);
request.addQueryParameter(x-ms-lease-action, break);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.LeaseBreakPeriod).empty())
{
    request.addHeader(k_HeaderLeaseBreakPeriod, std::to_string(options.LeaseBreakPeriod));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerBreakLeaseResponse
{
std::string ETag;
std::string LastModified;
uint32_t LeaseTime;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerBreakLeaseResponse ContainerBreakLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerBreakLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The Break operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseTime = std::stoull(response.getHeaders().get("x-ms-lease-time"));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerBreakLease(std::string url, const ContainerBreakLeaseOptions& containerBreakLeaseOptions)
{
return ContainerBreakLeaseParseResponse(Azure::Core::Http::Client::Send(ContainerBreakLeaseCreateRequest(url, containerBreakLeaseOptions)));
};

struct ContainerChangeLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string ProposedLeaseIdRequired; // Proposed lease ID, in a GUID string format. The Blob service returns 400 (Invalid request) if the proposed lease ID is not in the correct format. See Guid Constructor (String) for a list of valid GUID string formats.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerChangeLeaseCreateRequest(std::string url, const ContainerChangeLeaseOptions& containerChangeLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(restype, container);
request.addQueryParameter(x-ms-lease-action, change);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
request.addHeader(k_HeaderProposedLeaseIdRequired, options.ProposedLeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerChangeLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string LeaseId;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerChangeLeaseResponse ContainerChangeLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerChangeLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Change operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerChangeLease(std::string url, const ContainerChangeLeaseOptions& containerChangeLeaseOptions)
{
return ContainerChangeLeaseParseResponse(Azure::Core::Http::Client::Send(ContainerChangeLeaseCreateRequest(url, containerChangeLeaseOptions)));
};

struct ContainerListBlobFlatSegmentOptions
{
std::string Prefix = std::string(); // Filters the results to return only containers whose name begins with the specified prefix.
std::string Marker = std::string(); // A string value that identifies the portion of the list of containers to be returned with the next listing operation. The operation returns the NextMarker value within the response body if the listing operation did not return all containers remaining to be listed with the current page. The NextMarker value can be used as the value for the marker parameter in a subsequent call to request the next page of list items. The marker value is opaque to the client.
uint32_t MaxResults = uint32_t(); // Specifies the maximum number of containers to return. If the request does not specify maxresults, or specifies a value greater than 5000, the server will return up to 5000 items. Note that if the listing operation crosses a partition boundary, then the service will return a continuation token for retrieving the remainder of the results. For this reason, it is possible that the service will return fewer results than specified by maxresults, or than the default of 5000.
std::vector<string> ListBlobsInclude = std::vector<string>(); // Include this parameter to specify one or more datasets to include in the response.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerListBlobFlatSegmentCreateRequest(std::string url, const ContainerListBlobFlatSegmentOptions& containerListBlobFlatSegmentOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, container);
request.addQueryParameter(comp, list);
if (!options.Prefix.empty())
{
    request.addHeader(k_QueryPrefix, options.Prefix);
}if (!options.Marker.empty())
{
    request.addHeader(k_QueryMarker, options.Marker);
}if (!std::to_string(options.MaxResults).empty())
{
    request.addHeader(k_QueryMaxResults, std::to_string(options.MaxResults));
}if (!options.ListBlobsInclude.empty())
{
    request.addHeader(k_QueryListBlobsInclude, options.ListBlobsInclude);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerListBlobFlatSegmentResponse
{
ListBlobsFlatSegmentResponse ListBlobsFlatSegmentResponse;
std::string ContentType;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerListBlobFlatSegmentResponse ContainerListBlobFlatSegmentParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerListBlobFlatSegmentResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.ListBlobsFlatSegmentResponse = ListBlobsFlatSegmentResponse::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerListBlobFlatSegment(std::string url, const ContainerListBlobFlatSegmentOptions& containerListBlobFlatSegmentOptions)
{
return ContainerListBlobFlatSegmentParseResponse(Azure::Core::Http::Client::Send(ContainerListBlobFlatSegmentCreateRequest(url, containerListBlobFlatSegmentOptions)));
};

struct ContainerListBlobHierarchySegmentOptions
{
std::string Prefix = std::string(); // Filters the results to return only containers whose name begins with the specified prefix.
std::string Delimiter; // When the request includes this parameter, the operation returns a BlobPrefix element in the response body that acts as a placeholder for all blobs whose names begin with the same substring up to the appearance of the delimiter character. The delimiter may be a single character or a string.
std::string Marker = std::string(); // A string value that identifies the portion of the list of containers to be returned with the next listing operation. The operation returns the NextMarker value within the response body if the listing operation did not return all containers remaining to be listed with the current page. The NextMarker value can be used as the value for the marker parameter in a subsequent call to request the next page of list items. The marker value is opaque to the client.
uint32_t MaxResults = uint32_t(); // Specifies the maximum number of containers to return. If the request does not specify maxresults, or specifies a value greater than 5000, the server will return up to 5000 items. Note that if the listing operation crosses a partition boundary, then the service will return a continuation token for retrieving the remainder of the results. For this reason, it is possible that the service will return fewer results than specified by maxresults, or than the default of 5000.
std::vector<string> ListBlobsInclude = std::vector<string>(); // Include this parameter to specify one or more datasets to include in the response.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request ContainerListBlobHierarchySegmentCreateRequest(std::string url, const ContainerListBlobHierarchySegmentOptions& containerListBlobHierarchySegmentOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, container);
request.addQueryParameter(comp, list);
if (!options.Prefix.empty())
{
    request.addHeader(k_QueryPrefix, options.Prefix);
}request.addQueryParameter(k_QueryDelimiter, options.Delimiter);
if (!options.Marker.empty())
{
    request.addHeader(k_QueryMarker, options.Marker);
}if (!std::to_string(options.MaxResults).empty())
{
    request.addHeader(k_QueryMaxResults, std::to_string(options.MaxResults));
}if (!options.ListBlobsInclude.empty())
{
    request.addHeader(k_QueryListBlobsInclude, options.ListBlobsInclude);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct ContainerListBlobHierarchySegmentResponse
{
ListBlobsHierarchySegmentResponse ListBlobsHierarchySegmentResponse;
std::string ContentType;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static ContainerListBlobHierarchySegmentResponse ContainerListBlobHierarchySegmentParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerListBlobHierarchySegmentResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success.
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.ListBlobsHierarchySegmentResponse = ListBlobsHierarchySegmentResponse::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerListBlobHierarchySegment(std::string url, const ContainerListBlobHierarchySegmentOptions& containerListBlobHierarchySegmentOptions)
{
return ContainerListBlobHierarchySegmentParseResponse(Azure::Core::Http::Client::Send(ContainerListBlobHierarchySegmentCreateRequest(url, containerListBlobHierarchySegmentOptions)));
};

struct ContainerGetAccountInfoOptions
{
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request ContainerGetAccountInfoCreateRequest(std::string url, const ContainerGetAccountInfoOptions& containerGetAccountInfoOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, account);
request.addQueryParameter(comp, properties);
request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct ContainerGetAccountInfoResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string SkuName;
std::string AccountKind;
};

static ContainerGetAccountInfoResponse ContainerGetAccountInfoParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
ContainerGetAccountInfoResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success (OK)
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.SkuName = response.getHeaders().get("x-ms-sku-name");
result.AccountKind = response.getHeaders().get("x-ms-account-kind");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response ContainerGetAccountInfo(std::string url, const ContainerGetAccountInfoOptions& containerGetAccountInfoOptions)
{
return ContainerGetAccountInfoParseResponse(Azure::Core::Http::Client::Send(ContainerGetAccountInfoCreateRequest(url, containerGetAccountInfoOptions)));
};

struct DirectoryCreateOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string DirectoryProperties = std::string(); // Optional.  User-defined properties to be stored with the file or directory, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is base64 encoded.
std::string PosixPermissions = std::string(); // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
std::string PosixUmask = std::string(); // Only valid if Hierarchical Namespace is enabled for the account. This umask restricts permission settings for file and directory, and will only be applied when default Acl does not exist in parent directory. If the umask bit has set, it means that the corresponding permission will be disabled. Otherwise the corresponding permission will be determined by the permission. A 4-digit octal notation (e.g. 0022) is supported here. If no umask was specified, a default umask - 0027 will be used.
std::string XMsCacheControl = std::string(); // Cache control for given resource
std::string XMsContentType = std::string(); // Content type for given resource
std::string XMsContentEncoding = std::string(); // Content encoding for given resource
std::string XMsContentLanguage = std::string(); // Content language for given resource
std::string XMsContentDisposition = std::string(); // Content disposition for given resource
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request DirectoryCreateCreateRequest(std::string url, const DirectoryCreateOptions& directoryCreateOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(resource, directory);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.DirectoryProperties.empty())
{
    request.addHeader(k_HeaderDirectoryProperties, options.DirectoryProperties);
}if (!options.PosixPermissions.empty())
{
    request.addHeader(k_HeaderPosixPermissions, options.PosixPermissions);
}if (!options.PosixUmask.empty())
{
    request.addHeader(k_HeaderPosixUmask, options.PosixUmask);
}if (!options.XMsCacheControl.empty())
{
    request.addHeader(k_HeaderXMsCacheControl, options.XMsCacheControl);
}if (!options.XMsContentType.empty())
{
    request.addHeader(k_HeaderXMsContentType, options.XMsContentType);
}if (!options.XMsContentEncoding.empty())
{
    request.addHeader(k_HeaderXMsContentEncoding, options.XMsContentEncoding);
}if (!options.XMsContentLanguage.empty())
{
    request.addHeader(k_HeaderXMsContentLanguage, options.XMsContentLanguage);
}if (!options.XMsContentDisposition.empty())
{
    request.addHeader(k_HeaderXMsContentDisposition, options.XMsContentDisposition);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct DirectoryCreateResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
uint32_t ContentLength;
std::string Date;
};

static DirectoryCreateResponse DirectoryCreateParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
DirectoryCreateResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The file or directory was created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.Date = response.getHeaders().get("Date");
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response DirectoryCreate(std::string url, const DirectoryCreateOptions& directoryCreateOptions)
{
return DirectoryCreateParseResponse(Azure::Core::Http::Client::Send(DirectoryCreateCreateRequest(url, directoryCreateOptions)));
};

struct DirectoryRenameOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string Continuation = std::string(); // When renaming a directory, the number of paths that are renamed with each invocation is limited.  If the number of paths to be renamed exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the rename operation to continue renaming the directory.
std::string PathRenameMode = std::string(); // Determines the behavior of the rename operation
std::string FileRenameSource; // The file or directory to be renamed. The value must have the following format: "/{filesysystem}/{path}".  If "x-ms-properties" is specified, the properties will overwrite the existing properties; otherwise, the existing properties will be preserved.
std::string DirectoryProperties = std::string(); // Optional.  User-defined properties to be stored with the file or directory, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is base64 encoded.
std::string PosixPermissions = std::string(); // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
std::string PosixUmask = std::string(); // Only valid if Hierarchical Namespace is enabled for the account. This umask restricts permission settings for file and directory, and will only be applied when default Acl does not exist in parent directory. If the umask bit has set, it means that the corresponding permission will be disabled. Otherwise the corresponding permission will be determined by the permission. A 4-digit octal notation (e.g. 0022) is supported here. If no umask was specified, a default umask - 0027 will be used.
std::string XMsCacheControl = std::string(); // Cache control for given resource
std::string XMsContentType = std::string(); // Content type for given resource
std::string XMsContentEncoding = std::string(); // Content encoding for given resource
std::string XMsContentLanguage = std::string(); // Content language for given resource
std::string XMsContentDisposition = std::string(); // Content disposition for given resource
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string SourceLeaseId = std::string(); // A lease ID for the source path. If specified, the source path must have an active lease and the leaase ID must match.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request DirectoryRenameCreateRequest(std::string url, const DirectoryRenameOptions& directoryRenameOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.Continuation.empty())
{
    request.addHeader(k_QueryContinuation, options.Continuation);
}if (!options.PathRenameMode.empty())
{
    request.addHeader(k_QueryPathRenameMode, options.PathRenameMode);
}request.addHeader(k_HeaderFileRenameSource, options.FileRenameSource);
if (!options.DirectoryProperties.empty())
{
    request.addHeader(k_HeaderDirectoryProperties, options.DirectoryProperties);
}if (!options.PosixPermissions.empty())
{
    request.addHeader(k_HeaderPosixPermissions, options.PosixPermissions);
}if (!options.PosixUmask.empty())
{
    request.addHeader(k_HeaderPosixUmask, options.PosixUmask);
}if (!options.XMsCacheControl.empty())
{
    request.addHeader(k_HeaderXMsCacheControl, options.XMsCacheControl);
}if (!options.XMsContentType.empty())
{
    request.addHeader(k_HeaderXMsContentType, options.XMsContentType);
}if (!options.XMsContentEncoding.empty())
{
    request.addHeader(k_HeaderXMsContentEncoding, options.XMsContentEncoding);
}if (!options.XMsContentLanguage.empty())
{
    request.addHeader(k_HeaderXMsContentLanguage, options.XMsContentLanguage);
}if (!options.XMsContentDisposition.empty())
{
    request.addHeader(k_HeaderXMsContentDisposition, options.XMsContentDisposition);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.SourceLeaseId.empty())
{
    request.addHeader(k_HeaderSourceLeaseId, options.SourceLeaseId);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct DirectoryRenameResponse
{
std::string marker;
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
uint32_t ContentLength;
std::string Date;
};

static DirectoryRenameResponse DirectoryRenameParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
DirectoryRenameResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The directory was renamed.
result.marker = response.getHeaders().get("x-ms-continuation");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.Date = response.getHeaders().get("Date");
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response DirectoryRename(std::string url, const DirectoryRenameOptions& directoryRenameOptions)
{
return DirectoryRenameParseResponse(Azure::Core::Http::Client::Send(DirectoryRenameCreateRequest(url, directoryRenameOptions)));
};

struct DirectoryDeleteOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
bool RecursiveDirectoryDelete; // If "true", all paths beneath the directory will be deleted. If "false" and the directory is non-empty, an error occurs.
std::string Continuation = std::string(); // When renaming a directory, the number of paths that are renamed with each invocation is limited.  If the number of paths to be renamed exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the rename operation to continue renaming the directory.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request DirectoryDeleteCreateRequest(std::string url, const DirectoryDeleteOptions& directoryDeleteOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::delete, url);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addQueryParameter(k_QueryRecursiveDirectoryDelete, std::to_string(options.RecursiveDirectoryDelete));
if (!options.Continuation.empty())
{
    request.addHeader(k_QueryContinuation, options.Continuation);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct DirectoryDeleteResponse
{
std::string marker;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static DirectoryDeleteResponse DirectoryDeleteParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
DirectoryDeleteResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The directory was deleted.
result.marker = response.getHeaders().get("x-ms-continuation");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response DirectoryDelete(std::string url, const DirectoryDeleteOptions& directoryDeleteOptions)
{
return DirectoryDeleteParseResponse(Azure::Core::Http::Client::Send(DirectoryDeleteCreateRequest(url, directoryDeleteOptions)));
};

struct DirectorySetAccessControlOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string Owner = std::string(); // Optional. The owner of the blob or directory.
std::string Group = std::string(); // Optional. The owning group of the blob or directory.
std::string PosixPermissions = std::string(); // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
std::string PosixAcl = std::string(); // Sets POSIX access control rights on files and directories. The value is a comma-separated list of access control entries. Each access control entry (ACE) consists of a scope, a type, a user or group identifier, and permissions in the format "[scope:][type]:[id]:[permissions]".
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request DirectorySetAccessControlCreateRequest(std::string url, const DirectorySetAccessControlOptions& directorySetAccessControlOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::patch, url);
request.addQueryParameter(action, setAccessControl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.Owner.empty())
{
    request.addHeader(k_HeaderOwner, options.Owner);
}if (!options.Group.empty())
{
    request.addHeader(k_HeaderGroup, options.Group);
}if (!options.PosixPermissions.empty())
{
    request.addHeader(k_HeaderPosixPermissions, options.PosixPermissions);
}if (!options.PosixAcl.empty())
{
    request.addHeader(k_HeaderPosixAcl, options.PosixAcl);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct DirectorySetAccessControlResponse
{
std::string Date;
std::string ETag;
std::string LastModified;
std::string RequestId;
std::string Version;
};

static DirectorySetAccessControlResponse DirectorySetAccessControlParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
DirectorySetAccessControlResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Set directory access control response.
result.Date = response.getHeaders().get("Date");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response DirectorySetAccessControl(std::string url, const DirectorySetAccessControlOptions& directorySetAccessControlOptions)
{
return DirectorySetAccessControlParseResponse(Azure::Core::Http::Client::Send(DirectorySetAccessControlCreateRequest(url, directorySetAccessControlOptions)));
};

struct DirectoryGetAccessControlOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
bool Upn = bool(); // Optional. Valid only when Hierarchical Namespace is enabled for the account. If "true", the identity values returned in the x-ms-owner, x-ms-group, and x-ms-acl response headers will be transformed from Azure Active Directory Object IDs to User Principal Names.  If "false", the values will be returned as Azure Active Directory Object IDs. The default value is false.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request DirectoryGetAccessControlCreateRequest(std::string url, const DirectoryGetAccessControlOptions& directoryGetAccessControlOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::head, url);
request.addQueryParameter(action, getAccessControl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.Upn).empty())
{
    request.addHeader(k_QueryUpn, std::to_string(options.Upn));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct DirectoryGetAccessControlResponse
{
std::string Date;
std::string ETag;
std::string LastModified;
std::string XMsOwner;
std::string XMsGroup;
std::string XMsPermissions;
std::string XMsAcl;
std::string RequestId;
std::string Version;
};

static DirectoryGetAccessControlResponse DirectoryGetAccessControlParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
DirectoryGetAccessControlResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Get directory access control response.
result.Date = response.getHeaders().get("Date");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.XMsOwner = response.getHeaders().get(k_HeaderOwner);
result.XMsGroup = response.getHeaders().get(k_HeaderGroup);
result.XMsPermissions = response.getHeaders().get(k_HeaderPosixPermissions);
result.XMsAcl = response.getHeaders().get(k_HeaderPosixAcl);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response DirectoryGetAccessControl(std::string url, const DirectoryGetAccessControlOptions& directoryGetAccessControlOptions)
{
return DirectoryGetAccessControlParseResponse(Azure::Core::Http::Client::Send(DirectoryGetAccessControlCreateRequest(url, directoryGetAccessControlOptions)));
};

struct BlobDownloadOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string Range = std::string(); // Return only the bytes of the blob in the specified range.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
bool GetRangeContentMD5 = bool(); // When set to true and specified together with the Range, the service returns the MD5 hash for the range, as long as the range is less than or equal to 4 MB in size.
bool GetRangeContentCRC64 = bool(); // When set to true and specified together with the Range, the service returns the CRC64 hash for the range, as long as the range is less than or equal to 4 MB in size.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobDownloadCreateRequest(std::string url, const BlobDownloadOptions& blobDownloadOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.Range.empty())
{
    request.addHeader(k_HeaderRange, options.Range);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!std::to_string(options.GetRangeContentMD5).empty())
{
    request.addHeader(k_HeaderGetRangeContentMD5, std::to_string(options.GetRangeContentMD5));
}if (!std::to_string(options.GetRangeContentCRC64).empty())
{
    request.addHeader(k_HeaderGetRangeContentCRC64, std::to_string(options.GetRangeContentCRC64));
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobDownloadResponse
{
Azure::Core::Http::BodyBuffer BodyBuffer;
std::string LastModified;
std::string Metadata;
uint32_t ContentLength;
std::string ContentType;
std::string ContentRange;
std::string ETag;
std::string ContentMD5;
std::string ContentEncoding;
std::string CacheControl;
std::string ContentDisposition;
std::string ContentLanguage;
uint32_t BlobSequenceNumber;
std::string BlobType;
std::string CopyCompletionTime;
std::string CopyStatusDescription;
std::string CopyId;
std::string CopyProgress;
std::string CopySource;
std::string CopyStatus;
std::string LeaseDuration;
std::string LeaseState;
std::string LeaseStatus;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string AcceptRanges;
std::string Date;
uint32_t BlobCommittedBlockCount;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
std::string BlobContentMD5;
std::string ContentCrc64;
};

static BlobDownloadResponse BlobDownloadParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobDownloadResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Returns the content of the entire blob.
result.LastModified = response.getHeaders().get("Last-Modified");
result.Metadata = response.getHeaders().get(k_HeaderMetadata);
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.ContentRange = response.getHeaders().get("Content-Range");
result.ETag = response.getHeaders().get("ETag");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ContentEncoding = response.getHeaders().get("Content-Encoding");
result.CacheControl = response.getHeaders().get("Cache-Control");
result.ContentDisposition = response.getHeaders().get("Content-Disposition");
result.ContentLanguage = response.getHeaders().get("Content-Language");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.BlobType = response.getHeaders().get("x-ms-blob-type");
result.CopyCompletionTime = response.getHeaders().get("x-ms-copy-completion-time");
result.CopyStatusDescription = response.getHeaders().get("x-ms-copy-status-description");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyProgress = response.getHeaders().get("x-ms-copy-progress");
result.CopySource = response.getHeaders().get(k_HeaderCopySource);
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
result.LeaseDuration = response.getHeaders().get(k_HeaderLeaseDuration);
result.LeaseState = response.getHeaders().get("x-ms-lease-state");
result.LeaseStatus = response.getHeaders().get("x-ms-lease-status");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.AcceptRanges = response.getHeaders().get("Accept-Ranges");
result.Date = response.getHeaders().get("Date");
result.BlobCommittedBlockCount = std::stoull(response.getHeaders().get("x-ms-blob-committed-block-count"));
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
result.BlobContentMD5 = response.getHeaders().get(k_HeaderBlobContentMD5);
result.BodyBuffer = response.getBodyBuffer();
}
else if (std::to_string(response.getStatusCode()) == "206")
{
// Returns the content of a specified range of the blob.
result.LastModified = response.getHeaders().get("Last-Modified");
result.Metadata = response.getHeaders().get(k_HeaderMetadata);
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.ContentRange = response.getHeaders().get("Content-Range");
result.ETag = response.getHeaders().get("ETag");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ContentEncoding = response.getHeaders().get("Content-Encoding");
result.CacheControl = response.getHeaders().get("Cache-Control");
result.ContentDisposition = response.getHeaders().get("Content-Disposition");
result.ContentLanguage = response.getHeaders().get("Content-Language");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.BlobType = response.getHeaders().get("x-ms-blob-type");
result.ContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.CopyCompletionTime = response.getHeaders().get("x-ms-copy-completion-time");
result.CopyStatusDescription = response.getHeaders().get("x-ms-copy-status-description");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyProgress = response.getHeaders().get("x-ms-copy-progress");
result.CopySource = response.getHeaders().get(k_HeaderCopySource);
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
result.LeaseDuration = response.getHeaders().get(k_HeaderLeaseDuration);
result.LeaseState = response.getHeaders().get("x-ms-lease-state");
result.LeaseStatus = response.getHeaders().get("x-ms-lease-status");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.AcceptRanges = response.getHeaders().get("Accept-Ranges");
result.Date = response.getHeaders().get("Date");
result.BlobCommittedBlockCount = std::stoull(response.getHeaders().get("x-ms-blob-committed-block-count"));
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
result.BlobContentMD5 = response.getHeaders().get(k_HeaderBlobContentMD5);
result.BodyBuffer = response.getBodyBuffer();
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobDownload(std::string url, const BlobDownloadOptions& blobDownloadOptions)
{
return BlobDownloadParseResponse(Azure::Core::Http::Client::Send(BlobDownloadCreateRequest(url, blobDownloadOptions)));
};

struct BlobGetPropertiesOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobGetPropertiesCreateRequest(std::string url, const BlobGetPropertiesOptions& blobGetPropertiesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::head, url);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobGetPropertiesResponse
{
std::string LastModified;
std::string CreationTime;
std::string Metadata;
std::string BlobType;
std::string CopyCompletionTime;
std::string CopyStatusDescription;
std::string CopyId;
std::string CopyProgress;
std::string CopySource;
std::string CopyStatus;
bool IsIncrementalCopy;
std::string DestinationSnapshot;
std::string LeaseDuration;
std::string LeaseState;
std::string LeaseStatus;
uint32_t ContentLength;
std::string ContentType;
std::string ETag;
std::string ContentMD5;
std::string ContentEncoding;
std::string ContentDisposition;
std::string ContentLanguage;
std::string CacheControl;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string AcceptRanges;
uint32_t BlobCommittedBlockCount;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
std::string AccessTier;
bool AccessTierInferred;
std::string ArchiveStatus;
std::string AccessTierChangeTime;
};

static BlobGetPropertiesResponse BlobGetPropertiesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobGetPropertiesResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Returns the properties of the blob.
result.LastModified = response.getHeaders().get("Last-Modified");
result.CreationTime = response.getHeaders().get("x-ms-creation-time");
result.Metadata = response.getHeaders().get(k_HeaderMetadata);
result.BlobType = response.getHeaders().get("x-ms-blob-type");
result.CopyCompletionTime = response.getHeaders().get("x-ms-copy-completion-time");
result.CopyStatusDescription = response.getHeaders().get("x-ms-copy-status-description");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyProgress = response.getHeaders().get("x-ms-copy-progress");
result.CopySource = response.getHeaders().get(k_HeaderCopySource);
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
result.IsIncrementalCopy = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-incremental-copy")));
result.DestinationSnapshot = response.getHeaders().get("x-ms-copy-destination-snapshot");
result.LeaseDuration = response.getHeaders().get(k_HeaderLeaseDuration);
result.LeaseState = response.getHeaders().get("x-ms-lease-state");
result.LeaseStatus = response.getHeaders().get("x-ms-lease-status");
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.ETag = response.getHeaders().get("ETag");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ContentEncoding = response.getHeaders().get("Content-Encoding");
result.ContentDisposition = response.getHeaders().get("Content-Disposition");
result.ContentLanguage = response.getHeaders().get("Content-Language");
result.CacheControl = response.getHeaders().get("Cache-Control");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.AcceptRanges = response.getHeaders().get("Accept-Ranges");
result.BlobCommittedBlockCount = std::stoull(response.getHeaders().get("x-ms-blob-committed-block-count"));
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
result.AccessTier = response.getHeaders().get(k_HeaderAccessTierRequired);
result.AccessTierInferred = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-access-tier-inferred")));
result.ArchiveStatus = response.getHeaders().get("x-ms-archive-status");
result.AccessTierChangeTime = response.getHeaders().get("x-ms-access-tier-change-time");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobGetProperties(std::string url, const BlobGetPropertiesOptions& blobGetPropertiesOptions)
{
return BlobGetPropertiesParseResponse(Azure::Core::Http::Client::Send(BlobGetPropertiesCreateRequest(url, blobGetPropertiesOptions)));
};

struct BlobDeleteOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string DeleteSnapshots = std::string(); // Required if the blob has associated snapshots. Specify one of the following two options: include: Delete the base blob and all of its snapshots. only: Delete only the blob's snapshots and not the blob itself
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobDeleteCreateRequest(std::string url, const BlobDeleteOptions& blobDeleteOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::delete, url);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.DeleteSnapshots.empty())
{
    request.addHeader(k_HeaderDeleteSnapshots, options.DeleteSnapshots);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobDeleteResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobDeleteResponse BlobDeleteParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobDeleteResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The delete request was accepted and the blob will be deleted.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobDelete(std::string url, const BlobDeleteOptions& blobDeleteOptions)
{
return BlobDeleteParseResponse(Azure::Core::Http::Client::Send(BlobDeleteCreateRequest(url, blobDeleteOptions)));
};

struct BlobSetAccessControlOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string Owner = std::string(); // Optional. The owner of the blob or directory.
std::string Group = std::string(); // Optional. The owning group of the blob or directory.
std::string PosixPermissions = std::string(); // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
std::string PosixAcl = std::string(); // Sets POSIX access control rights on files and directories. The value is a comma-separated list of access control entries. Each access control entry (ACE) consists of a scope, a type, a user or group identifier, and permissions in the format "[scope:][type]:[id]:[permissions]".
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request BlobSetAccessControlCreateRequest(std::string url, const BlobSetAccessControlOptions& blobSetAccessControlOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::patch, url);
request.addQueryParameter(action, setAccessControl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.Owner.empty())
{
    request.addHeader(k_HeaderOwner, options.Owner);
}if (!options.Group.empty())
{
    request.addHeader(k_HeaderGroup, options.Group);
}if (!options.PosixPermissions.empty())
{
    request.addHeader(k_HeaderPosixPermissions, options.PosixPermissions);
}if (!options.PosixAcl.empty())
{
    request.addHeader(k_HeaderPosixAcl, options.PosixAcl);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct BlobSetAccessControlResponse
{
std::string Date;
std::string ETag;
std::string LastModified;
std::string RequestId;
std::string Version;
};

static BlobSetAccessControlResponse BlobSetAccessControlParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobSetAccessControlResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Set blob access control response.
result.Date = response.getHeaders().get("Date");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobSetAccessControl(std::string url, const BlobSetAccessControlOptions& blobSetAccessControlOptions)
{
return BlobSetAccessControlParseResponse(Azure::Core::Http::Client::Send(BlobSetAccessControlCreateRequest(url, blobSetAccessControlOptions)));
};

struct BlobGetAccessControlOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
bool Upn = bool(); // Optional. Valid only when Hierarchical Namespace is enabled for the account. If "true", the identity values returned in the x-ms-owner, x-ms-group, and x-ms-acl response headers will be transformed from Azure Active Directory Object IDs to User Principal Names.  If "false", the values will be returned as Azure Active Directory Object IDs. The default value is false.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request BlobGetAccessControlCreateRequest(std::string url, const BlobGetAccessControlOptions& blobGetAccessControlOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::head, url);
request.addQueryParameter(action, getAccessControl);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.Upn).empty())
{
    request.addHeader(k_QueryUpn, std::to_string(options.Upn));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct BlobGetAccessControlResponse
{
std::string Date;
std::string ETag;
std::string LastModified;
std::string XMsOwner;
std::string XMsGroup;
std::string XMsPermissions;
std::string XMsAcl;
std::string RequestId;
std::string Version;
};

static BlobGetAccessControlResponse BlobGetAccessControlParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobGetAccessControlResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Get blob access control response.
result.Date = response.getHeaders().get("Date");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.XMsOwner = response.getHeaders().get(k_HeaderOwner);
result.XMsGroup = response.getHeaders().get(k_HeaderGroup);
result.XMsPermissions = response.getHeaders().get(k_HeaderPosixPermissions);
result.XMsAcl = response.getHeaders().get(k_HeaderPosixAcl);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobGetAccessControl(std::string url, const BlobGetAccessControlOptions& blobGetAccessControlOptions)
{
return BlobGetAccessControlParseResponse(Azure::Core::Http::Client::Send(BlobGetAccessControlCreateRequest(url, blobGetAccessControlOptions)));
};

struct BlobRenameOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string PathRenameMode = std::string(); // Determines the behavior of the rename operation
std::string FileRenameSource; // The file or directory to be renamed. The value must have the following format: "/{filesysystem}/{path}".  If "x-ms-properties" is specified, the properties will overwrite the existing properties; otherwise, the existing properties will be preserved.
std::string DirectoryProperties = std::string(); // Optional.  User-defined properties to be stored with the file or directory, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is base64 encoded.
std::string PosixPermissions = std::string(); // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
std::string PosixUmask = std::string(); // Only valid if Hierarchical Namespace is enabled for the account. This umask restricts permission settings for file and directory, and will only be applied when default Acl does not exist in parent directory. If the umask bit has set, it means that the corresponding permission will be disabled. Otherwise the corresponding permission will be determined by the permission. A 4-digit octal notation (e.g. 0022) is supported here. If no umask was specified, a default umask - 0027 will be used.
std::string XMsCacheControl = std::string(); // Cache control for given resource
std::string XMsContentType = std::string(); // Content type for given resource
std::string XMsContentEncoding = std::string(); // Content encoding for given resource
std::string XMsContentLanguage = std::string(); // Content language for given resource
std::string XMsContentDisposition = std::string(); // Content disposition for given resource
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string SourceLeaseId = std::string(); // A lease ID for the source path. If specified, the source path must have an active lease and the leaase ID must match.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobRenameCreateRequest(std::string url, const BlobRenameOptions& blobRenameOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.PathRenameMode.empty())
{
    request.addHeader(k_QueryPathRenameMode, options.PathRenameMode);
}request.addHeader(k_HeaderFileRenameSource, options.FileRenameSource);
if (!options.DirectoryProperties.empty())
{
    request.addHeader(k_HeaderDirectoryProperties, options.DirectoryProperties);
}if (!options.PosixPermissions.empty())
{
    request.addHeader(k_HeaderPosixPermissions, options.PosixPermissions);
}if (!options.PosixUmask.empty())
{
    request.addHeader(k_HeaderPosixUmask, options.PosixUmask);
}if (!options.XMsCacheControl.empty())
{
    request.addHeader(k_HeaderXMsCacheControl, options.XMsCacheControl);
}if (!options.XMsContentType.empty())
{
    request.addHeader(k_HeaderXMsContentType, options.XMsContentType);
}if (!options.XMsContentEncoding.empty())
{
    request.addHeader(k_HeaderXMsContentEncoding, options.XMsContentEncoding);
}if (!options.XMsContentLanguage.empty())
{
    request.addHeader(k_HeaderXMsContentLanguage, options.XMsContentLanguage);
}if (!options.XMsContentDisposition.empty())
{
    request.addHeader(k_HeaderXMsContentDisposition, options.XMsContentDisposition);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.SourceLeaseId.empty())
{
    request.addHeader(k_HeaderSourceLeaseId, options.SourceLeaseId);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobRenameResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
uint32_t ContentLength;
std::string Date;
};

static BlobRenameResponse BlobRenameParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobRenameResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The file was renamed.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.ContentLength = std::stoull(response.getHeaders().get(k_HeaderContentLength));
result.Date = response.getHeaders().get("Date");
}
else
{
throw DataLakeStorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobRename(std::string url, const BlobRenameOptions& blobRenameOptions)
{
return BlobRenameParseResponse(Azure::Core::Http::Client::Send(BlobRenameCreateRequest(url, blobRenameOptions)));
};

struct PageBlobCreateOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t ContentLength; // The length of the request.
std::string PremiumPageBlobAccessTierOptional = std::string(); // Optional. Indicates the tier to be set on the page blob.
std::string BlobContentType = std::string(); // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentEncoding = std::string(); // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentLanguage = std::string(); // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentMD5 = std::string(); // Optional. An MD5 hash of the blob content. Note that this hash is not validated, as the hashes for the individual blocks were validated when each was uploaded.
std::string BlobCacheControl = std::string(); // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string BlobContentDisposition = std::string(); // Optional. Sets the blob's Content-Disposition header.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
uint32_t BlobContentLengthRequired; // This header specifies the maximum size for the page blob, up to 1 TB. The page blob size must be aligned to a 512-byte boundary.
uint32_t BlobSequenceNumber = uint32_t(); // Set for page blobs only. The sequence number is a user-controlled value that you can use to track requests. The value of the sequence number must be between 0 and 2^63 - 1.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobCreateCreateRequest(std::string url, const PageBlobCreateOptions& pageBlobCreateOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(x-ms-blob-type, PageBlob);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.PremiumPageBlobAccessTierOptional.empty())
{
    request.addHeader(k_HeaderPremiumPageBlobAccessTierOptional, options.PremiumPageBlobAccessTierOptional);
}if (!options.BlobContentType.empty())
{
    request.addHeader(k_HeaderBlobContentType, options.BlobContentType);
}if (!options.BlobContentEncoding.empty())
{
    request.addHeader(k_HeaderBlobContentEncoding, options.BlobContentEncoding);
}if (!options.BlobContentLanguage.empty())
{
    request.addHeader(k_HeaderBlobContentLanguage, options.BlobContentLanguage);
}if (!options.BlobContentMD5.empty())
{
    request.addHeader(k_HeaderBlobContentMD5, options.BlobContentMD5);
}if (!options.BlobCacheControl.empty())
{
    request.addHeader(k_HeaderBlobCacheControl, options.BlobCacheControl);
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.BlobContentDisposition.empty())
{
    request.addHeader(k_HeaderBlobContentDisposition, options.BlobContentDisposition);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderBlobContentLengthRequired, std::to_string(options.BlobContentLengthRequired));
if (!std::to_string(options.BlobSequenceNumber).empty())
{
    request.addHeader(k_HeaderBlobSequenceNumber, std::to_string(options.BlobSequenceNumber));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobCreateResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static PageBlobCreateResponse PageBlobCreateParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobCreateResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The blob was created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobCreate(std::string url, const PageBlobCreateOptions& pageBlobCreateOptions)
{
return PageBlobCreateParseResponse(Azure::Core::Http::Client::Send(PageBlobCreateCreateRequest(url, pageBlobCreateOptions)));
};

struct AppendBlobCreateOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t ContentLength; // The length of the request.
std::string BlobContentType = std::string(); // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentEncoding = std::string(); // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentLanguage = std::string(); // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentMD5 = std::string(); // Optional. An MD5 hash of the blob content. Note that this hash is not validated, as the hashes for the individual blocks were validated when each was uploaded.
std::string BlobCacheControl = std::string(); // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string BlobContentDisposition = std::string(); // Optional. Sets the blob's Content-Disposition header.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request AppendBlobCreateCreateRequest(std::string url, const AppendBlobCreateOptions& appendBlobCreateOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(x-ms-blob-type, AppendBlob);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.BlobContentType.empty())
{
    request.addHeader(k_HeaderBlobContentType, options.BlobContentType);
}if (!options.BlobContentEncoding.empty())
{
    request.addHeader(k_HeaderBlobContentEncoding, options.BlobContentEncoding);
}if (!options.BlobContentLanguage.empty())
{
    request.addHeader(k_HeaderBlobContentLanguage, options.BlobContentLanguage);
}if (!options.BlobContentMD5.empty())
{
    request.addHeader(k_HeaderBlobContentMD5, options.BlobContentMD5);
}if (!options.BlobCacheControl.empty())
{
    request.addHeader(k_HeaderBlobCacheControl, options.BlobCacheControl);
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.BlobContentDisposition.empty())
{
    request.addHeader(k_HeaderBlobContentDisposition, options.BlobContentDisposition);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct AppendBlobCreateResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static AppendBlobCreateResponse AppendBlobCreateParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
AppendBlobCreateResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The blob was created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response AppendBlobCreate(std::string url, const AppendBlobCreateOptions& appendBlobCreateOptions)
{
return AppendBlobCreateParseResponse(Azure::Core::Http::Client::Send(AppendBlobCreateCreateRequest(url, appendBlobCreateOptions)));
};

struct BlockBlobUploadOptions
{
Azure::Core::Http::BodyBuffer* Body; // Initial data
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
uint32_t ContentLength; // The length of the request.
std::string BlobContentType = std::string(); // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentEncoding = std::string(); // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentLanguage = std::string(); // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentMD5 = std::string(); // Optional. An MD5 hash of the blob content. Note that this hash is not validated, as the hashes for the individual blocks were validated when each was uploaded.
std::string BlobCacheControl = std::string(); // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string BlobContentDisposition = std::string(); // Optional. Sets the blob's Content-Disposition header.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string AccessTierOptional = std::string(); // Optional. Indicates the tier to be set on the blob.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlockBlobUploadCreateRequest(std::string url, const BlockBlobUploadOptions& blockBlobUploadOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(x-ms-blob-type, BlockBlob);
request.setBodyBuffer(options.Body);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.BlobContentType.empty())
{
    request.addHeader(k_HeaderBlobContentType, options.BlobContentType);
}if (!options.BlobContentEncoding.empty())
{
    request.addHeader(k_HeaderBlobContentEncoding, options.BlobContentEncoding);
}if (!options.BlobContentLanguage.empty())
{
    request.addHeader(k_HeaderBlobContentLanguage, options.BlobContentLanguage);
}if (!options.BlobContentMD5.empty())
{
    request.addHeader(k_HeaderBlobContentMD5, options.BlobContentMD5);
}if (!options.BlobCacheControl.empty())
{
    request.addHeader(k_HeaderBlobCacheControl, options.BlobCacheControl);
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.BlobContentDisposition.empty())
{
    request.addHeader(k_HeaderBlobContentDisposition, options.BlobContentDisposition);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.AccessTierOptional.empty())
{
    request.addHeader(k_HeaderAccessTierOptional, options.AccessTierOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlockBlobUploadResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static BlockBlobUploadResponse BlockBlobUploadParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlockBlobUploadResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The blob was updated.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlockBlobUpload(std::string url, const BlockBlobUploadOptions& blockBlobUploadOptions)
{
return BlockBlobUploadParseResponse(Azure::Core::Http::Client::Send(BlockBlobUploadCreateRequest(url, blockBlobUploadOptions)));
};

struct BlobUndeleteOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobUndeleteCreateRequest(std::string url, const BlobUndeleteOptions& blobUndeleteOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, undelete);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobUndeleteResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobUndeleteResponse BlobUndeleteParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobUndeleteResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The blob was undeleted successfully.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobUndelete(std::string url, const BlobUndeleteOptions& blobUndeleteOptions)
{
return BlobUndeleteParseResponse(Azure::Core::Http::Client::Send(BlobUndeleteCreateRequest(url, blobUndeleteOptions)));
};

struct BlobSetHTTPHeadersOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string BlobCacheControl = std::string(); // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentType = std::string(); // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentMD5 = std::string(); // Optional. An MD5 hash of the blob content. Note that this hash is not validated, as the hashes for the individual blocks were validated when each was uploaded.
std::string BlobContentEncoding = std::string(); // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentLanguage = std::string(); // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string BlobContentDisposition = std::string(); // Optional. Sets the blob's Content-Disposition header.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobSetHTTPHeadersCreateRequest(std::string url, const BlobSetHTTPHeadersOptions& blobSetHTTPHeadersOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, properties);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.BlobCacheControl.empty())
{
    request.addHeader(k_HeaderBlobCacheControl, options.BlobCacheControl);
}if (!options.BlobContentType.empty())
{
    request.addHeader(k_HeaderBlobContentType, options.BlobContentType);
}if (!options.BlobContentMD5.empty())
{
    request.addHeader(k_HeaderBlobContentMD5, options.BlobContentMD5);
}if (!options.BlobContentEncoding.empty())
{
    request.addHeader(k_HeaderBlobContentEncoding, options.BlobContentEncoding);
}if (!options.BlobContentLanguage.empty())
{
    request.addHeader(k_HeaderBlobContentLanguage, options.BlobContentLanguage);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.BlobContentDisposition.empty())
{
    request.addHeader(k_HeaderBlobContentDisposition, options.BlobContentDisposition);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobSetHTTPHeadersResponse
{
std::string ETag;
std::string LastModified;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobSetHTTPHeadersResponse BlobSetHTTPHeadersParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobSetHTTPHeadersResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The properties were set successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobSetHTTPHeaders(std::string url, const BlobSetHTTPHeadersOptions& blobSetHTTPHeadersOptions)
{
return BlobSetHTTPHeadersParseResponse(Azure::Core::Http::Client::Send(BlobSetHTTPHeadersCreateRequest(url, blobSetHTTPHeadersOptions)));
};

struct BlobSetMetadataOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobSetMetadataCreateRequest(std::string url, const BlobSetMetadataOptions& blobSetMetadataOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, metadata);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobSetMetadataResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static BlobSetMetadataResponse BlobSetMetadataParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobSetMetadataResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The metadata was set successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobSetMetadata(std::string url, const BlobSetMetadataOptions& blobSetMetadataOptions)
{
return BlobSetMetadataParseResponse(Azure::Core::Http::Client::Send(BlobSetMetadataCreateRequest(url, blobSetMetadataOptions)));
};

struct BlobAcquireLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t LeaseDuration = uint32_t(); // Specifies the duration of the lease, in seconds, or negative one (-1) for a lease that never expires. A non-infinite lease can be between 15 and 60 seconds. A lease duration cannot be changed using renew or change.
std::string ProposedLeaseIdOptional = std::string(); // Proposed lease ID, in a GUID string format. The Blob service returns 400 (Invalid request) if the proposed lease ID is not in the correct format. See Guid Constructor (String) for a list of valid GUID string formats.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobAcquireLeaseCreateRequest(std::string url, const BlobAcquireLeaseOptions& blobAcquireLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(x-ms-lease-action, acquire);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.LeaseDuration).empty())
{
    request.addHeader(k_HeaderLeaseDuration, std::to_string(options.LeaseDuration));
}if (!options.ProposedLeaseIdOptional.empty())
{
    request.addHeader(k_HeaderProposedLeaseIdOptional, options.ProposedLeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobAcquireLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string LeaseId;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobAcquireLeaseResponse BlobAcquireLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobAcquireLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The Acquire operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobAcquireLease(std::string url, const BlobAcquireLeaseOptions& blobAcquireLeaseOptions)
{
return BlobAcquireLeaseParseResponse(Azure::Core::Http::Client::Send(BlobAcquireLeaseCreateRequest(url, blobAcquireLeaseOptions)));
};

struct BlobReleaseLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobReleaseLeaseCreateRequest(std::string url, const BlobReleaseLeaseOptions& blobReleaseLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(x-ms-lease-action, release);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobReleaseLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobReleaseLeaseResponse BlobReleaseLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobReleaseLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Release operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobReleaseLease(std::string url, const BlobReleaseLeaseOptions& blobReleaseLeaseOptions)
{
return BlobReleaseLeaseParseResponse(Azure::Core::Http::Client::Send(BlobReleaseLeaseCreateRequest(url, blobReleaseLeaseOptions)));
};

struct BlobRenewLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobRenewLeaseCreateRequest(std::string url, const BlobRenewLeaseOptions& blobRenewLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(x-ms-lease-action, renew);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobRenewLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string LeaseId;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobRenewLeaseResponse BlobRenewLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobRenewLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Renew operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobRenewLease(std::string url, const BlobRenewLeaseOptions& blobRenewLeaseOptions)
{
return BlobRenewLeaseParseResponse(Azure::Core::Http::Client::Send(BlobRenewLeaseCreateRequest(url, blobRenewLeaseOptions)));
};

struct BlobChangeLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
std::string ProposedLeaseIdRequired; // Proposed lease ID, in a GUID string format. The Blob service returns 400 (Invalid request) if the proposed lease ID is not in the correct format. See Guid Constructor (String) for a list of valid GUID string formats.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobChangeLeaseCreateRequest(std::string url, const BlobChangeLeaseOptions& blobChangeLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(x-ms-lease-action, change);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderLeaseIdRequired, options.LeaseIdRequired);
request.addHeader(k_HeaderProposedLeaseIdRequired, options.ProposedLeaseIdRequired);
if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobChangeLeaseResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string LeaseId;
std::string Version;
std::string Date;
};

static BlobChangeLeaseResponse BlobChangeLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobChangeLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Change operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.LeaseId = response.getHeaders().get(k_HeaderLeaseIdOptional);
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobChangeLease(std::string url, const BlobChangeLeaseOptions& blobChangeLeaseOptions)
{
return BlobChangeLeaseParseResponse(Azure::Core::Http::Client::Send(BlobChangeLeaseCreateRequest(url, blobChangeLeaseOptions)));
};

struct BlobBreakLeaseOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t LeaseBreakPeriod = uint32_t(); // For a break operation, proposed duration the lease should continue before it is broken, in seconds, between 0 and 60. This break period is only used if it is shorter than the time remaining on the lease. If longer, the time remaining on the lease is used. A new lease will not be available before the break period has expired, but the lease may be held for longer than the break period. If this header does not appear with a break operation, a fixed-duration lease breaks after the remaining lease period elapses, and an infinite lease breaks immediately.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobBreakLeaseCreateRequest(std::string url, const BlobBreakLeaseOptions& blobBreakLeaseOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, lease);
request.addQueryParameter(x-ms-lease-action, break);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!std::to_string(options.LeaseBreakPeriod).empty())
{
    request.addHeader(k_HeaderLeaseBreakPeriod, std::to_string(options.LeaseBreakPeriod));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobBreakLeaseResponse
{
std::string ETag;
std::string LastModified;
uint32_t LeaseTime;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobBreakLeaseResponse BlobBreakLeaseParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobBreakLeaseResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The Break operation completed successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.LeaseTime = std::stoull(response.getHeaders().get("x-ms-lease-time"));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobBreakLease(std::string url, const BlobBreakLeaseOptions& blobBreakLeaseOptions)
{
return BlobBreakLeaseParseResponse(Azure::Core::Http::Client::Send(BlobBreakLeaseCreateRequest(url, blobBreakLeaseOptions)));
};

struct BlobCreateSnapshotOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobCreateSnapshotCreateRequest(std::string url, const BlobCreateSnapshotOptions& blobCreateSnapshotOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, snapshot);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobCreateSnapshotResponse
{
std::string Snapshot;
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
};

static BlobCreateSnapshotResponse BlobCreateSnapshotParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobCreateSnapshotResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The snaptshot was taken successfully.
result.Snapshot = response.getHeaders().get("x-ms-snapshot");
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobCreateSnapshot(std::string url, const BlobCreateSnapshotOptions& blobCreateSnapshotOptions)
{
return BlobCreateSnapshotParseResponse(Azure::Core::Http::Client::Send(BlobCreateSnapshotCreateRequest(url, blobCreateSnapshotOptions)));
};

struct BlobStartCopyFromURLOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string AccessTierOptional = std::string(); // Optional. Indicates the tier to be set on the blob.
std::string RehydratePriority = std::string(); // Optional: Indicates the priority with which to rehydrate an archived blob.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string CopySource; // Specifies the name of the source page blob snapshot. This value is a URL of up to 2 KB in length that specifies a page blob snapshot. The value should be URL-encoded as it would appear in a request URI. The source blob must either be public or must be authenticated via a shared access signature.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobStartCopyFromURLCreateRequest(std::string url, const BlobStartCopyFromURLOptions& blobStartCopyFromURLOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.AccessTierOptional.empty())
{
    request.addHeader(k_HeaderAccessTierOptional, options.AccessTierOptional);
}if (!options.RehydratePriority.empty())
{
    request.addHeader(k_HeaderRehydratePriority, options.RehydratePriority);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderCopySource, options.CopySource);
if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobStartCopyFromURLResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string CopyId;
std::string CopyStatus;
};

static BlobStartCopyFromURLResponse BlobStartCopyFromURLParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobStartCopyFromURLResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The copy blob has been accepted with the specified copy status.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobStartCopyFromURL(std::string url, const BlobStartCopyFromURLOptions& blobStartCopyFromURLOptions)
{
return BlobStartCopyFromURLParseResponse(Azure::Core::Http::Client::Send(BlobStartCopyFromURLCreateRequest(url, blobStartCopyFromURLOptions)));
};

struct BlobCopyFromURLOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string AccessTierOptional = std::string(); // Optional. Indicates the tier to be set on the blob.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string CopySource; // Specifies the name of the source page blob snapshot. This value is a URL of up to 2 KB in length that specifies a page blob snapshot. The value should be URL-encoded as it would appear in a request URI. The source blob must either be public or must be authenticated via a shared access signature.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string SourceContentMD5 = std::string(); // Specify the md5 calculated for the range of bytes that must be read from the copy source.

};

static Azure::Core::Http::Request BlobCopyFromURLCreateRequest(std::string url, const BlobCopyFromURLOptions& blobCopyFromURLOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(x-ms-requires-sync, true);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.AccessTierOptional.empty())
{
    request.addHeader(k_HeaderAccessTierOptional, options.AccessTierOptional);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderCopySource, options.CopySource);
if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}if (!options.SourceContentMD5.empty())
{
    request.addHeader(k_HeaderSourceContentMD5, options.SourceContentMD5);
}return request;
};

struct BlobCopyFromURLResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string CopyId;
std::string CopyStatus;
std::string ContentMD5;
std::string XMsContentCrc64;
};

static BlobCopyFromURLResponse BlobCopyFromURLParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobCopyFromURLResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The copy has completed.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobCopyFromURL(std::string url, const BlobCopyFromURLOptions& blobCopyFromURLOptions)
{
return BlobCopyFromURLParseResponse(Azure::Core::Http::Client::Send(BlobCopyFromURLCreateRequest(url, blobCopyFromURLOptions)));
};

struct BlobAbortCopyFromURLOptions
{
std::string CopyId; // The copy identifier provided in the x-ms-copy-id header of the original Copy Blob operation.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlobAbortCopyFromURLCreateRequest(std::string url, const BlobAbortCopyFromURLOptions& blobAbortCopyFromURLOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, copy);
request.addQueryParameter(x-ms-copy-action, abort);
request.addQueryParameter(k_QueryCopyId, options.CopyId);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlobAbortCopyFromURLResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlobAbortCopyFromURLResponse BlobAbortCopyFromURLParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobAbortCopyFromURLResponse result;
if (std::to_string(response.getStatusCode()) == "204")
{
// The delete request was accepted and the blob will be deleted.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobAbortCopyFromURL(std::string url, const BlobAbortCopyFromURLOptions& blobAbortCopyFromURLOptions)
{
return BlobAbortCopyFromURLParseResponse(Azure::Core::Http::Client::Send(BlobAbortCopyFromURLCreateRequest(url, blobAbortCopyFromURLOptions)));
};

struct BlobSetTierOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string AccessTierRequired; // Indicates the tier to be set on the blob.
std::string RehydratePriority = std::string(); // Optional: Indicates the priority with which to rehydrate an archived blob.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.

};

static Azure::Core::Http::Request BlobSetTierCreateRequest(std::string url, const BlobSetTierOptions& blobSetTierOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, tier);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderAccessTierRequired, options.AccessTierRequired);
if (!options.RehydratePriority.empty())
{
    request.addHeader(k_HeaderRehydratePriority, options.RehydratePriority);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}return request;
};

struct BlobSetTierResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
};

static BlobSetTierResponse BlobSetTierParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobSetTierResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The new tier will take effect immediately.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else if (std::to_string(response.getStatusCode()) == "202")
{
// The transition to the new tier is pending.
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobSetTier(std::string url, const BlobSetTierOptions& blobSetTierOptions)
{
return BlobSetTierParseResponse(Azure::Core::Http::Client::Send(BlobSetTierCreateRequest(url, blobSetTierOptions)));
};

struct BlobGetAccountInfoOptions
{
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.

};

static Azure::Core::Http::Request BlobGetAccountInfoCreateRequest(std::string url, const BlobGetAccountInfoOptions& blobGetAccountInfoOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(restype, account);
request.addQueryParameter(comp, properties);
request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
return request;
};

struct BlobGetAccountInfoResponse
{
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string SkuName;
std::string AccountKind;
};

static BlobGetAccountInfoResponse BlobGetAccountInfoParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlobGetAccountInfoResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Success (OK)
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.SkuName = response.getHeaders().get("x-ms-sku-name");
result.AccountKind = response.getHeaders().get("x-ms-account-kind");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlobGetAccountInfo(std::string url, const BlobGetAccountInfoOptions& blobGetAccountInfoOptions)
{
return BlobGetAccountInfoParseResponse(Azure::Core::Http::Client::Send(BlobGetAccountInfoCreateRequest(url, blobGetAccountInfoOptions)));
};

struct BlockBlobStageBlockOptions
{
std::string BlockId; // A valid Base64 string value that identifies the block. Prior to encoding, the string must be less than or equal to 64 bytes in size. For a given blob, the length of the value specified for the blockid parameter must be the same size for each block.
uint32_t ContentLength; // The length of the request.
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
std::string ContentCrc64 = std::string(); // Specify the transactional crc64 for the body, to be validated by the service.
Azure::Core::Http::BodyBuffer* Body; // Initial data
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlockBlobStageBlockCreateRequest(std::string url, const BlockBlobStageBlockOptions& blockBlobStageBlockOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, block);
request.addQueryParameter(k_QueryBlockId, options.BlockId);
request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}if (!options.ContentCrc64.empty())
{
    request.addHeader(k_HeaderContentCrc64, options.ContentCrc64);
}request.setBodyBuffer(options.Body);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlockBlobStageBlockResponse
{
std::string ContentMD5;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string XMsContentCrc64;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static BlockBlobStageBlockResponse BlockBlobStageBlockParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlockBlobStageBlockResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The block was created.
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlockBlobStageBlock(std::string url, const BlockBlobStageBlockOptions& blockBlobStageBlockOptions)
{
return BlockBlobStageBlockParseResponse(Azure::Core::Http::Client::Send(BlockBlobStageBlockCreateRequest(url, blockBlobStageBlockOptions)));
};

struct BlockBlobStageBlockFromURLOptions
{
std::string BlockId; // A valid Base64 string value that identifies the block. Prior to encoding, the string must be less than or equal to 64 bytes in size. For a given blob, the length of the value specified for the blockid parameter must be the same size for each block.
uint32_t ContentLength; // The length of the request.
std::string SourceUrl; // Specify a URL to the copy source.
std::string SourceRange = std::string(); // Bytes of source data in the specified range.
std::string SourceContentMD5 = std::string(); // Specify the md5 calculated for the range of bytes that must be read from the copy source.
std::string SourceContentCRC64 = std::string(); // Specify the crc64 calculated for the range of bytes that must be read from the copy source.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlockBlobStageBlockFromURLCreateRequest(std::string url, const BlockBlobStageBlockFromURLOptions& blockBlobStageBlockFromURLOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, block);
request.addQueryParameter(k_QueryBlockId, options.BlockId);
request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
request.addHeader(k_HeaderSourceUrl, options.SourceUrl);
if (!options.SourceRange.empty())
{
    request.addHeader(k_HeaderSourceRange, options.SourceRange);
}if (!options.SourceContentMD5.empty())
{
    request.addHeader(k_HeaderSourceContentMD5, options.SourceContentMD5);
}if (!options.SourceContentCRC64.empty())
{
    request.addHeader(k_HeaderSourceContentCRC64, options.SourceContentCRC64);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlockBlobStageBlockFromURLResponse
{
std::string ContentMD5;
std::string XMsContentCrc64;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static BlockBlobStageBlockFromURLResponse BlockBlobStageBlockFromURLParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlockBlobStageBlockFromURLResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The block was created.
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlockBlobStageBlockFromURL(std::string url, const BlockBlobStageBlockFromURLOptions& blockBlobStageBlockFromURLOptions)
{
return BlockBlobStageBlockFromURLParseResponse(Azure::Core::Http::Client::Send(BlockBlobStageBlockFromURLCreateRequest(url, blockBlobStageBlockFromURLOptions)));
};

struct BlockBlobCommitBlockListOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string BlobCacheControl = std::string(); // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentType = std::string(); // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentEncoding = std::string(); // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentLanguage = std::string(); // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
std::string BlobContentMD5 = std::string(); // Optional. An MD5 hash of the blob content. Note that this hash is not validated, as the hashes for the individual blocks were validated when each was uploaded.
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
std::string ContentCrc64 = std::string(); // Specify the transactional crc64 for the body, to be validated by the service.
std::map<std::string, std::string> Metadata = std::map<std::string, std::string>(); // Optional. Specifies a user-defined name-value pair associated with the blob. If no name-value pairs are specified, the operation will copy the metadata from the source blob or file to the destination blob. If one or more name-value pairs are specified, the destination blob is created with the specified metadata, and metadata is not copied from the source blob or file. Note that beginning with version 2009-09-19, metadata names must adhere to the naming rules for C# identifiers. See Naming and Referencing Containers, Blobs, and Metadata for more information.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string BlobContentDisposition = std::string(); // Optional. Sets the blob's Content-Disposition header.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string AccessTierOptional = std::string(); // Optional. Indicates the tier to be set on the blob.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
BlockLookupList BlockLookupList; // None
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlockBlobCommitBlockListCreateRequest(std::string url, const BlockBlobCommitBlockListOptions& blockBlobCommitBlockListOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, blocklist);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.BlobCacheControl.empty())
{
    request.addHeader(k_HeaderBlobCacheControl, options.BlobCacheControl);
}if (!options.BlobContentType.empty())
{
    request.addHeader(k_HeaderBlobContentType, options.BlobContentType);
}if (!options.BlobContentEncoding.empty())
{
    request.addHeader(k_HeaderBlobContentEncoding, options.BlobContentEncoding);
}if (!options.BlobContentLanguage.empty())
{
    request.addHeader(k_HeaderBlobContentLanguage, options.BlobContentLanguage);
}if (!options.BlobContentMD5.empty())
{
    request.addHeader(k_HeaderBlobContentMD5, options.BlobContentMD5);
}if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}if (!options.ContentCrc64.empty())
{
    request.addHeader(k_HeaderContentCrc64, options.ContentCrc64);
}for (const auto& pair : options.Metadata)
{
    request.addHeader(k_HeaderMetadata + pair.first, pair.second);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.BlobContentDisposition.empty())
{
    request.addHeader(k_HeaderBlobContentDisposition, options.BlobContentDisposition);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.AccessTierOptional.empty())
{
    request.addHeader(k_HeaderAccessTierOptional, options.AccessTierOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlockBlobCommitBlockListResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static BlockBlobCommitBlockListResponse BlockBlobCommitBlockListParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlockBlobCommitBlockListResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The block list was recorded.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlockBlobCommitBlockList(std::string url, const BlockBlobCommitBlockListOptions& blockBlobCommitBlockListOptions)
{
return BlockBlobCommitBlockListParseResponse(Azure::Core::Http::Client::Send(BlockBlobCommitBlockListCreateRequest(url, blockBlobCommitBlockListOptions)));
};

struct BlockBlobGetBlockListOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
std::string BlockListType; // Specifies whether to return the list of committed blocks, the list of uncommitted blocks, or both lists together.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request BlockBlobGetBlockListCreateRequest(std::string url, const BlockBlobGetBlockListOptions& blockBlobGetBlockListOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(comp, blocklist);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}request.addQueryParameter(k_QueryBlockListType, options.BlockListType);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct BlockBlobGetBlockListResponse
{
BlockList BlockList;
std::string LastModified;
std::string ETag;
std::string ContentType;
uint32_t BlobContentLength;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static BlockBlobGetBlockListResponse BlockBlobGetBlockListParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
BlockBlobGetBlockListResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The page range was written.
result.LastModified = response.getHeaders().get("Last-Modified");
result.ETag = response.getHeaders().get("ETag");
result.ContentType = response.getHeaders().get(k_HeaderMultipartContentType);
result.BlobContentLength = std::stoull(response.getHeaders().get(k_HeaderBlobContentLengthOptional));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.BlockList = BlockList::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response BlockBlobGetBlockList(std::string url, const BlockBlobGetBlockListOptions& blockBlobGetBlockListOptions)
{
return BlockBlobGetBlockListParseResponse(Azure::Core::Http::Client::Send(BlockBlobGetBlockListCreateRequest(url, blockBlobGetBlockListOptions)));
};

struct PageBlobUploadPagesOptions
{
Azure::Core::Http::BodyBuffer* Body; // Initial data
uint32_t ContentLength; // The length of the request.
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
std::string ContentCrc64 = std::string(); // Specify the transactional crc64 for the body, to be validated by the service.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string Range = std::string(); // Return only the bytes of the blob in the specified range.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
uint32_t IfSequenceNumberLessThanOrEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than or equal to the specified.
uint32_t IfSequenceNumberLessThan = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than the specified.
uint32_t IfSequenceNumberEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has the specified sequence number.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobUploadPagesCreateRequest(std::string url, const PageBlobUploadPagesOptions& pageBlobUploadPagesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, page);
request.addQueryParameter(x-ms-page-write, update);
request.setBodyBuffer(options.Body);
request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}if (!options.ContentCrc64.empty())
{
    request.addHeader(k_HeaderContentCrc64, options.ContentCrc64);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.Range.empty())
{
    request.addHeader(k_HeaderRange, options.Range);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!std::to_string(options.IfSequenceNumberLessThanOrEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThanOrEqualTo, std::to_string(options.IfSequenceNumberLessThanOrEqualTo));
}if (!std::to_string(options.IfSequenceNumberLessThan).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThan, std::to_string(options.IfSequenceNumberLessThan));
}if (!std::to_string(options.IfSequenceNumberEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberEqualTo, std::to_string(options.IfSequenceNumberEqualTo));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobUploadPagesResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static PageBlobUploadPagesResponse PageBlobUploadPagesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobUploadPagesResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The page range was written.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobUploadPages(std::string url, const PageBlobUploadPagesOptions& pageBlobUploadPagesOptions)
{
return PageBlobUploadPagesParseResponse(Azure::Core::Http::Client::Send(PageBlobUploadPagesCreateRequest(url, pageBlobUploadPagesOptions)));
};

struct PageBlobClearPagesOptions
{
uint32_t ContentLength; // The length of the request.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string Range = std::string(); // Return only the bytes of the blob in the specified range.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
uint32_t IfSequenceNumberLessThanOrEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than or equal to the specified.
uint32_t IfSequenceNumberLessThan = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than the specified.
uint32_t IfSequenceNumberEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has the specified sequence number.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobClearPagesCreateRequest(std::string url, const PageBlobClearPagesOptions& pageBlobClearPagesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, page);
request.addQueryParameter(x-ms-page-write, clear);
request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.Range.empty())
{
    request.addHeader(k_HeaderRange, options.Range);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!std::to_string(options.IfSequenceNumberLessThanOrEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThanOrEqualTo, std::to_string(options.IfSequenceNumberLessThanOrEqualTo));
}if (!std::to_string(options.IfSequenceNumberLessThan).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThan, std::to_string(options.IfSequenceNumberLessThan));
}if (!std::to_string(options.IfSequenceNumberEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberEqualTo, std::to_string(options.IfSequenceNumberEqualTo));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobClearPagesResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static PageBlobClearPagesResponse PageBlobClearPagesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobClearPagesResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The page range was cleared.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobClearPages(std::string url, const PageBlobClearPagesOptions& pageBlobClearPagesOptions)
{
return PageBlobClearPagesParseResponse(Azure::Core::Http::Client::Send(PageBlobClearPagesCreateRequest(url, pageBlobClearPagesOptions)));
};

struct PageBlobUploadPagesFromURLOptions
{
std::string SourceUrl; // Specify a URL to the copy source.
std::string SourceRangeRequiredPutPageFromUrl; // Bytes of source data in the specified range. The length of this range should match the ContentLength header and x-ms-range/Range destination range header.
std::string SourceContentMD5 = std::string(); // Specify the md5 calculated for the range of bytes that must be read from the copy source.
std::string SourceContentCRC64 = std::string(); // Specify the crc64 calculated for the range of bytes that must be read from the copy source.
uint32_t ContentLength; // The length of the request.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string RangeRequiredPutPageFromUrl; // The range of bytes to which the source range would be written. The range should be 512 aligned and range-end is required.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
uint32_t IfSequenceNumberLessThanOrEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than or equal to the specified.
uint32_t IfSequenceNumberLessThan = uint32_t(); // Specify this header value to operate only on a blob if it has a sequence number less than the specified.
uint32_t IfSequenceNumberEqualTo = uint32_t(); // Specify this header value to operate only on a blob if it has the specified sequence number.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobUploadPagesFromURLCreateRequest(std::string url, const PageBlobUploadPagesFromURLOptions& pageBlobUploadPagesFromURLOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, page);
request.addQueryParameter(x-ms-page-write, update);
request.addHeader(k_HeaderSourceUrl, options.SourceUrl);
request.addHeader(k_HeaderSourceRangeRequiredPutPageFromUrl, options.SourceRangeRequiredPutPageFromUrl);
if (!options.SourceContentMD5.empty())
{
    request.addHeader(k_HeaderSourceContentMD5, options.SourceContentMD5);
}if (!options.SourceContentCRC64.empty())
{
    request.addHeader(k_HeaderSourceContentCRC64, options.SourceContentCRC64);
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderRangeRequiredPutPageFromUrl, options.RangeRequiredPutPageFromUrl);
if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!std::to_string(options.IfSequenceNumberLessThanOrEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThanOrEqualTo, std::to_string(options.IfSequenceNumberLessThanOrEqualTo));
}if (!std::to_string(options.IfSequenceNumberLessThan).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberLessThan, std::to_string(options.IfSequenceNumberLessThan));
}if (!std::to_string(options.IfSequenceNumberEqualTo).empty())
{
    request.addHeader(k_HeaderIfSequenceNumberEqualTo, std::to_string(options.IfSequenceNumberEqualTo));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobUploadPagesFromURLResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
uint32_t BlobSequenceNumber;
std::string RequestId;
std::string Version;
std::string Date;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static PageBlobUploadPagesFromURLResponse PageBlobUploadPagesFromURLParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobUploadPagesFromURLResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The page range was written.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobUploadPagesFromURL(std::string url, const PageBlobUploadPagesFromURLOptions& pageBlobUploadPagesFromURLOptions)
{
return PageBlobUploadPagesFromURLParseResponse(Azure::Core::Http::Client::Send(PageBlobUploadPagesFromURLCreateRequest(url, pageBlobUploadPagesFromURLOptions)));
};

struct PageBlobGetPageRangesOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string Range = std::string(); // Return only the bytes of the blob in the specified range.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobGetPageRangesCreateRequest(std::string url, const PageBlobGetPageRangesOptions& pageBlobGetPageRangesOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(comp, pagelist);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.Range.empty())
{
    request.addHeader(k_HeaderRange, options.Range);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobGetPageRangesResponse
{
PageList PageList;
std::string LastModified;
std::string ETag;
uint32_t BlobContentLength;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static PageBlobGetPageRangesResponse PageBlobGetPageRangesParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobGetPageRangesResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Information on the page blob was found.
result.LastModified = response.getHeaders().get("Last-Modified");
result.ETag = response.getHeaders().get("ETag");
result.BlobContentLength = std::stoull(response.getHeaders().get(k_HeaderBlobContentLengthOptional));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.PageList = PageList::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobGetPageRanges(std::string url, const PageBlobGetPageRangesOptions& pageBlobGetPageRangesOptions)
{
return PageBlobGetPageRangesParseResponse(Azure::Core::Http::Client::Send(PageBlobGetPageRangesCreateRequest(url, pageBlobGetPageRangesOptions)));
};

struct PageBlobGetPageRangesDiffOptions
{
std::string Snapshot = std::string(); // The snapshot parameter is an opaque DateTime value that, when present, specifies the blob snapshot to retrieve. For more information on working with blob snapshots, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/creating-a-snapshot-of-a-blob">Creating a Snapshot of a Blob.</a>
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string PrevSnapshot = std::string(); // Optional in version 2015-07-08 and newer. The prevsnapshot parameter is a DateTime value that specifies that the response will contain only pages that were changed between target blob and previous snapshot. Changed pages include both updated and cleared pages. The target blob may be a snapshot, as long as the snapshot specified by prevsnapshot is the older of the two. Note that incremental snapshots are currently supported only for blobs created on or after January 1, 2016.
std::string Range = std::string(); // Return only the bytes of the blob in the specified range.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobGetPageRangesDiffCreateRequest(std::string url, const PageBlobGetPageRangesDiffOptions& pageBlobGetPageRangesDiffOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::get, url);
request.addQueryParameter(comp, pagelist);
if (!options.Snapshot.empty())
{
    request.addHeader(k_QuerySnapshot, options.Snapshot);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.PrevSnapshot.empty())
{
    request.addHeader(k_QueryPrevSnapshot, options.PrevSnapshot);
}if (!options.Range.empty())
{
    request.addHeader(k_HeaderRange, options.Range);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobGetPageRangesDiffResponse
{
PageList PageList;
std::string LastModified;
std::string ETag;
uint32_t BlobContentLength;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static PageBlobGetPageRangesDiffResponse PageBlobGetPageRangesDiffParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobGetPageRangesDiffResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// Information on the page blob was found.
result.LastModified = response.getHeaders().get("Last-Modified");
result.ETag = response.getHeaders().get("ETag");
result.BlobContentLength = std::stoull(response.getHeaders().get(k_HeaderBlobContentLengthOptional));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.PageList = PageList::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobGetPageRangesDiff(std::string url, const PageBlobGetPageRangesDiffOptions& pageBlobGetPageRangesDiffOptions)
{
return PageBlobGetPageRangesDiffParseResponse(Azure::Core::Http::Client::Send(PageBlobGetPageRangesDiffCreateRequest(url, pageBlobGetPageRangesDiffOptions)));
};

struct PageBlobResizeOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
uint32_t BlobContentLengthRequired; // This header specifies the maximum size for the page blob, up to 1 TB. The page blob size must be aligned to a 512-byte boundary.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobResizeCreateRequest(std::string url, const PageBlobResizeOptions& pageBlobResizeOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, properties);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderBlobContentLengthRequired, std::to_string(options.BlobContentLengthRequired));
request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobResizeResponse
{
std::string ETag;
std::string LastModified;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static PageBlobResizeResponse PageBlobResizeParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobResizeResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The Blob was resized successfully
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobResize(std::string url, const PageBlobResizeOptions& pageBlobResizeOptions)
{
return PageBlobResizeParseResponse(Azure::Core::Http::Client::Send(PageBlobResizeCreateRequest(url, pageBlobResizeOptions)));
};

struct PageBlobUpdateSequenceNumberOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string SequenceNumberAction; // Required if the x-ms-blob-sequence-number header is set for the request. This property applies to page blobs only. This property indicates how the service should modify the blob's sequence number
uint32_t BlobSequenceNumber = uint32_t(); // Set for page blobs only. The sequence number is a user-controlled value that you can use to track requests. The value of the sequence number must be between 0 and 2^63 - 1.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobUpdateSequenceNumberCreateRequest(std::string url, const PageBlobUpdateSequenceNumberOptions& pageBlobUpdateSequenceNumberOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, properties);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderSequenceNumberAction, options.SequenceNumberAction);
if (!std::to_string(options.BlobSequenceNumber).empty())
{
    request.addHeader(k_HeaderBlobSequenceNumber, std::to_string(options.BlobSequenceNumber));
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobUpdateSequenceNumberResponse
{
std::string ETag;
std::string LastModified;
uint32_t BlobSequenceNumber;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
};

static PageBlobUpdateSequenceNumberResponse PageBlobUpdateSequenceNumberParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobUpdateSequenceNumberResponse result;
if (std::to_string(response.getStatusCode()) == "200")
{
// The sequence numbers were updated successfully.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.BlobSequenceNumber = std::stoull(response.getHeaders().get(k_HeaderBlobSequenceNumber));
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobUpdateSequenceNumber(std::string url, const PageBlobUpdateSequenceNumberOptions& pageBlobUpdateSequenceNumberOptions)
{
return PageBlobUpdateSequenceNumberParseResponse(Azure::Core::Http::Client::Send(PageBlobUpdateSequenceNumberCreateRequest(url, pageBlobUpdateSequenceNumberOptions)));
};

struct PageBlobCopyIncrementalOptions
{
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string CopySource; // Specifies the name of the source page blob snapshot. This value is a URL of up to 2 KB in length that specifies a page blob snapshot. The value should be URL-encoded as it would appear in a request URI. The source blob must either be public or must be authenticated via a shared access signature.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request PageBlobCopyIncrementalCreateRequest(std::string url, const PageBlobCopyIncrementalOptions& pageBlobCopyIncrementalOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, incrementalcopy);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderCopySource, options.CopySource);
request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct PageBlobCopyIncrementalResponse
{
std::string ETag;
std::string LastModified;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string CopyId;
std::string CopyStatus;
};

static PageBlobCopyIncrementalResponse PageBlobCopyIncrementalParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
PageBlobCopyIncrementalResponse result;
if (std::to_string(response.getStatusCode()) == "202")
{
// The blob was copied.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.CopyId = response.getHeaders().get("x-ms-copy-id");
result.CopyStatus = response.getHeaders().get("x-ms-copy-status");
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response PageBlobCopyIncremental(std::string url, const PageBlobCopyIncrementalOptions& pageBlobCopyIncrementalOptions)
{
return PageBlobCopyIncrementalParseResponse(Azure::Core::Http::Client::Send(PageBlobCopyIncrementalCreateRequest(url, pageBlobCopyIncrementalOptions)));
};

struct AppendBlobAppendBlockOptions
{
Azure::Core::Http::BodyBuffer* Body; // Initial data
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t ContentLength; // The length of the request.
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
std::string ContentCrc64 = std::string(); // Specify the transactional crc64 for the body, to be validated by the service.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
uint32_t BlobConditionMaxSize = uint32_t(); // Optional conditional header. The max length in bytes permitted for the append blob. If the Append Block operation would cause the blob to exceed that limit or if the blob size is already greater than the value specified in this header, the request will fail with MaxBlobSizeConditionNotMet error (HTTP status code 412 - Precondition Failed).
uint32_t BlobConditionAppendPos = uint32_t(); // Optional conditional header, used only for the Append Block operation. A number indicating the byte offset to compare. Append Block will succeed only if the append position is equal to this number. If it is not, the request will fail with the AppendPositionConditionNotMet error (HTTP status code 412 - Precondition Failed).
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request AppendBlobAppendBlockCreateRequest(std::string url, const AppendBlobAppendBlockOptions& appendBlobAppendBlockOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, appendblock);
request.setBodyBuffer(options.Body);
if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}if (!options.ContentCrc64.empty())
{
    request.addHeader(k_HeaderContentCrc64, options.ContentCrc64);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!std::to_string(options.BlobConditionMaxSize).empty())
{
    request.addHeader(k_HeaderBlobConditionMaxSize, std::to_string(options.BlobConditionMaxSize));
}if (!std::to_string(options.BlobConditionAppendPos).empty())
{
    request.addHeader(k_HeaderBlobConditionAppendPos, std::to_string(options.BlobConditionAppendPos));
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct AppendBlobAppendBlockResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
std::string ClientRequestId;
std::string RequestId;
std::string Version;
std::string Date;
std::string BlobAppendOffset;
uint32_t BlobCommittedBlockCount;
bool IsServerEncrypted;
std::string EncryptionKeySha256;
};

static AppendBlobAppendBlockResponse AppendBlobAppendBlockParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
AppendBlobAppendBlockResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The block was created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.ClientRequestId = response.getHeaders().get(k_HeaderClientRequestId);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.BlobAppendOffset = response.getHeaders().get("x-ms-blob-append-offset");
result.BlobCommittedBlockCount = std::stoull(response.getHeaders().get("x-ms-blob-committed-block-count"));
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response AppendBlobAppendBlock(std::string url, const AppendBlobAppendBlockOptions& appendBlobAppendBlockOptions)
{
return AppendBlobAppendBlockParseResponse(Azure::Core::Http::Client::Send(AppendBlobAppendBlockCreateRequest(url, appendBlobAppendBlockOptions)));
};

struct AppendBlobAppendBlockFromUrlOptions
{
std::string SourceUrl; // Specify a URL to the copy source.
std::string SourceRange = std::string(); // Bytes of source data in the specified range.
std::string SourceContentMD5 = std::string(); // Specify the md5 calculated for the range of bytes that must be read from the copy source.
std::string SourceContentCRC64 = std::string(); // Specify the crc64 calculated for the range of bytes that must be read from the copy source.
uint32_t Timeout = uint32_t(); // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
uint32_t ContentLength; // The length of the request.
std::string ContentMD5 = std::string(); // Specify the transactional md5 for the body, to be validated by the service.
std::string EncryptionKey = std::string(); // Optional. Specifies the encryption key to use to encrypt the data provided in the request. If not specified, encryption is performed with the root account encryption key.  For more information, see Encryption at Rest for Azure Storage Services.
std::string EncryptionKeySha256 = std::string(); // The SHA-256 hash of the provided encryption key. Must be provided if the x-ms-encryption-key header is provided.
std::string EncryptionAlgorithm = std::string(); // The algorithm used to produce the encryption key hash. Currently, the only accepted value is "AES256". Must be provided if the x-ms-encryption-key header is provided.
std::string LeaseIdOptional = std::string(); // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
uint32_t BlobConditionMaxSize = uint32_t(); // Optional conditional header. The max length in bytes permitted for the append blob. If the Append Block operation would cause the blob to exceed that limit or if the blob size is already greater than the value specified in this header, the request will fail with MaxBlobSizeConditionNotMet error (HTTP status code 412 - Precondition Failed).
uint32_t BlobConditionAppendPos = uint32_t(); // Optional conditional header, used only for the Append Block operation. A number indicating the byte offset to compare. Append Block will succeed only if the append position is equal to this number. If it is not, the request will fail with the AppendPositionConditionNotMet error (HTTP status code 412 - Precondition Failed).
std::string IfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string IfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string IfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string IfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string SourceIfModifiedSince = std::string(); // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
std::string SourceIfUnmodifiedSince = std::string(); // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
std::string SourceIfMatch = std::string(); // Specify an ETag value to operate only on blobs with a matching value.
std::string SourceIfNoneMatch = std::string(); // Specify an ETag value to operate only on blobs without a matching value.
std::string ApiVersionParameter; // Specifies the version of the operation to use for this request.
std::string ClientRequestId = std::string(); // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.

};

static Azure::Core::Http::Request AppendBlobAppendBlockFromUrlCreateRequest(std::string url, const AppendBlobAppendBlockFromUrlOptions& appendBlobAppendBlockFromUrlOptions)
{
Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::put, url);
request.addQueryParameter(comp, appendblock);
request.addHeader(k_HeaderSourceUrl, options.SourceUrl);
if (!options.SourceRange.empty())
{
    request.addHeader(k_HeaderSourceRange, options.SourceRange);
}if (!options.SourceContentMD5.empty())
{
    request.addHeader(k_HeaderSourceContentMD5, options.SourceContentMD5);
}if (!options.SourceContentCRC64.empty())
{
    request.addHeader(k_HeaderSourceContentCRC64, options.SourceContentCRC64);
}if (!std::to_string(options.Timeout).empty())
{
    request.addHeader(k_QueryTimeout, std::to_string(options.Timeout));
}request.addHeader(k_HeaderContentLength, std::to_string(options.ContentLength));
if (!options.ContentMD5.empty())
{
    request.addHeader(k_HeaderContentMD5, options.ContentMD5);
}if (!options.EncryptionKey.empty())
{
    request.addHeader(k_HeaderEncryptionKey, options.EncryptionKey);
}if (!options.EncryptionKeySha256.empty())
{
    request.addHeader(k_HeaderEncryptionKeySha256, options.EncryptionKeySha256);
}if (!options.EncryptionAlgorithm.empty())
{
    request.addHeader(k_HeaderEncryptionAlgorithm, options.EncryptionAlgorithm);
}if (!options.LeaseIdOptional.empty())
{
    request.addHeader(k_HeaderLeaseIdOptional, options.LeaseIdOptional);
}if (!std::to_string(options.BlobConditionMaxSize).empty())
{
    request.addHeader(k_HeaderBlobConditionMaxSize, std::to_string(options.BlobConditionMaxSize));
}if (!std::to_string(options.BlobConditionAppendPos).empty())
{
    request.addHeader(k_HeaderBlobConditionAppendPos, std::to_string(options.BlobConditionAppendPos));
}if (!options.IfModifiedSince.empty())
{
    request.addHeader(k_HeaderIfModifiedSince, options.IfModifiedSince);
}if (!options.IfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderIfUnmodifiedSince, options.IfUnmodifiedSince);
}if (!options.IfMatch.empty())
{
    request.addHeader(k_HeaderIfMatch, options.IfMatch);
}if (!options.IfNoneMatch.empty())
{
    request.addHeader(k_HeaderIfNoneMatch, options.IfNoneMatch);
}if (!options.SourceIfModifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfModifiedSince, options.SourceIfModifiedSince);
}if (!options.SourceIfUnmodifiedSince.empty())
{
    request.addHeader(k_HeaderSourceIfUnmodifiedSince, options.SourceIfUnmodifiedSince);
}if (!options.SourceIfMatch.empty())
{
    request.addHeader(k_HeaderSourceIfMatch, options.SourceIfMatch);
}if (!options.SourceIfNoneMatch.empty())
{
    request.addHeader(k_HeaderSourceIfNoneMatch, options.SourceIfNoneMatch);
}request.addHeader(k_HeaderApiVersionParameter, options.ApiVersionParameter);
if (!options.ClientRequestId.empty())
{
    request.addHeader(k_HeaderClientRequestId, options.ClientRequestId);
}return request;
};

struct AppendBlobAppendBlockFromUrlResponse
{
std::string ETag;
std::string LastModified;
std::string ContentMD5;
std::string XMsContentCrc64;
std::string RequestId;
std::string Version;
std::string Date;
std::string BlobAppendOffset;
uint32_t BlobCommittedBlockCount;
std::string EncryptionKeySha256;
bool IsServerEncrypted;
};

static AppendBlobAppendBlockFromUrlResponse AppendBlobAppendBlockFromUrlParseResponse(/*const*/ Azure::Core::Http::Response& response)
{
AppendBlobAppendBlockFromUrlResponse result;
if (std::to_string(response.getStatusCode()) == "201")
{
// The block was created.
result.ETag = response.getHeaders().get("ETag");
result.LastModified = response.getHeaders().get("Last-Modified");
result.ContentMD5 = response.getHeaders().get(k_HeaderContentMD5);
result.XMsContentCrc64 = response.getHeaders().get(k_HeaderContentCrc64);
result.RequestId = response.getHeaders().get("x-ms-request-id");
result.Version = response.getHeaders().get(k_HeaderApiVersionParameter);
result.Date = response.getHeaders().get("Date");
result.BlobAppendOffset = response.getHeaders().get("x-ms-blob-append-offset");
result.BlobCommittedBlockCount = std::stoull(response.getHeaders().get("x-ms-blob-committed-block-count"));
result.EncryptionKeySha256 = response.getHeaders().get(k_HeaderEncryptionKeySha256);
result.IsServerEncrypted = static_cast<bool>(std::stoi(response.getHeaders().get("x-ms-request-server-encrypted")));
}
else
{
throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.getBodyBuffer()));
}
return result;
};

static Azure::Core::Http::Response AppendBlobAppendBlockFromUrl(std::string url, const AppendBlobAppendBlockFromUrlOptions& appendBlobAppendBlockFromUrlOptions)
{
return AppendBlobAppendBlockFromUrlParseResponse(Azure::Core::Http::Client::Send(AppendBlobAppendBlockFromUrlCreateRequest(url, appendBlobAppendBlockFromUrlOptions)));
};


};  // class BlobRestClient

}  // namespace Blobs
}  // namespace Storage
}  // namspace Azure

