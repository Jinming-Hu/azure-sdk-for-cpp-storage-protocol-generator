
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/***************************************************************
 * ALL THE CODE IN THIS FILE IS HANDWRITTEN, NOT AUTO-GENERATED.
 **************************************************************/

#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "http/curl/curl.hpp"
#include "http/http.hpp"
#include "json.hpp"

namespace Azure
{
namespace Storage
{
namespace ADLS
{

class ADLSRestClient
{
public:
  constexpr static const char* k_DefaultServiceApiVersion = "2019-12-12";
  constexpr static const char* k_PathDnsSuffixDefault = "dfs.core.windows.net";
  constexpr static const char* k_QueryFileSystemResource = "resource";
  constexpr static const char* k_QueryTimeout = "timeout";
  constexpr static const char* k_QueryRecursiveOptional = "recursive";
  constexpr static const char* k_QueryRecursiveRequired = "recursive";
  constexpr static const char* k_QueryContinuation = "continuation";
  constexpr static const char* k_QueryPathSetAccessControlRecursiveMode = "mode";
  constexpr static const char* k_QueryDirectory = "directory";
  constexpr static const char* k_QueryPrefix = "prefix";
  constexpr static const char* k_QueryMaxResults = "maxResults";
  constexpr static const char* k_QueryUpn = "upn";
  constexpr static const char* k_QueryPosition = "position";
  constexpr static const char* k_QueryRetainUncommittedData = "retainUncommittedData";
  constexpr static const char* k_QueryClose = "close";
  constexpr static const char* k_QueryResource = "resource";
  constexpr static const char* k_QueryPathResourceType = "resource";
  constexpr static const char* k_QueryPathRenameMode = "mode";
  constexpr static const char* k_QueryPathUpdateAction = "action";
  constexpr static const char* k_QueryMaxRecords = "maxRecords";
  constexpr static const char* k_QueryPathGetPropertiesAction = "action";
  constexpr static const char* k_QueryAction = "action";
  constexpr static const char* k_HeaderApiVersionParameter = "x-ms-version";
  constexpr static const char* k_HeaderClientRequestId = "x-ms-client-request-id";
  constexpr static const char* k_HeaderIfMatch = "If-Match";
  constexpr static const char* k_HeaderIfModifiedSince = "If-Modified-Since";
  constexpr static const char* k_HeaderIfNoneMatch = "If-None-Match";
  constexpr static const char* k_HeaderIfUnmodifiedSince = "If-Unmodified-Since";
  constexpr static const char* k_HeaderLeaseIdOptional = "x-ms-lease-id";
  constexpr static const char* k_HeaderLeaseIdRequired = "x-ms-lease-id";
  constexpr static const char* k_HeaderProposedLeaseIdOptional = "x-ms-proposed-lease-id";
  constexpr static const char* k_HeaderProperties = "x-ms-properties";
  constexpr static const char* k_HeaderSourceIfMatch = "x-ms-source-if-match";
  constexpr static const char* k_HeaderSourceIfModifiedSince = "x-ms-source-if-modified-since";
  constexpr static const char* k_HeaderSourceIfNoneMatch = "x-ms-source-if-none-match";
  constexpr static const char* k_HeaderSourceIfUnmodifiedSince = "x-ms-source-if-unmodified-since";
  constexpr static const char* k_HeaderSourceLeaseId = "x-ms-source-lease-id";
  constexpr static const char* k_HeaderCacheControl = "x-ms-cache-control";
  constexpr static const char* k_HeaderContentDisposition = "x-ms-content-disposition";
  constexpr static const char* k_HeaderContentEncoding = "x-ms-content-encoding";
  constexpr static const char* k_HeaderContentLanguage = "x-ms-content-language";
  constexpr static const char* k_HeaderContentType = "x-ms-content-type";
  constexpr static const char* k_HeaderTransactionalContentMD5 = "Content-MD5";
  constexpr static const char* k_HeaderContentMD5 = "x-ms-content-md5";
  constexpr static const char* k_HeaderUmask = "x-ms-umask";
  constexpr static const char* k_HeaderPermissions = "x-ms-permissions";
  constexpr static const char* k_HeaderRenameSource = "x-ms-rename-source";
  constexpr static const char* k_HeaderOwner = "x-ms-owner";
  constexpr static const char* k_HeaderGroup = "x-ms-group";
  constexpr static const char* k_HeaderAcl = "x-ms-acl";
  constexpr static const char* k_HeaderContentLength = "Content-Length";
  constexpr static const char* k_HeaderDate = "Date";
  constexpr static const char* k_HeaderXMsRequestId = "x-ms-request-id";
  constexpr static const char* k_HeaderXMsVersion = "x-ms-version";
  constexpr static const char* k_HeaderXMsContinuation = "x-ms-continuation";
  constexpr static const char* k_HeaderXMsErrorCode = "x-ms-error-code";
  constexpr static const char* k_HeaderETag = "ETag";
  constexpr static const char* k_HeaderLastModified = "Last-Modified";
  constexpr static const char* k_HeaderXMsNamespaceEnabled = "x-ms-namespace-enabled";
  constexpr static const char* k_HeaderXMsProperties = "x-ms-properties";
  constexpr static const char* k_HeaderAcceptRanges = "Accept-Ranges";
  constexpr static const char* k_HeaderContentRange = "Content-Range";
  constexpr static const char* k_HeaderPathLeaseAction = "x-ms-lease-action";
  constexpr static const char* k_HeaderXMsLeaseDuration = "x-ms-lease-duration";
  constexpr static const char* k_HeaderXMsLeaseBreakPeriod = "x-ms-lease-break-period";
  constexpr static const char* k_HeaderXMsLeaseId = "x-ms-lease-id";
  constexpr static const char* k_HeaderXMsLeaseTime = "x-ms-lease-time";
  constexpr static const char* k_HeaderRange = "Range";
  constexpr static const char* k_HeaderXMsRangeGetContentMd5 = "x-ms-range-get-content-md5";
  constexpr static const char* k_HeaderXMsResourceType = "x-ms-resource-type";
  constexpr static const char* k_HeaderXMsLeaseState = "x-ms-lease-state";
  constexpr static const char* k_HeaderXMsLeaseStatus = "x-ms-lease-status";
  constexpr static const char* k_HeaderXMsContentMd5 = "x-ms-content-md5";
  constexpr static const char* k_HeaderXMsOwner = "x-ms-owner";
  constexpr static const char* k_HeaderXMsGroup = "x-ms-group";
  constexpr static const char* k_HeaderXMsPermissions = "x-ms-permissions";
  constexpr static const char* k_HeaderXMsAcl = "x-ms-acl";
  constexpr static const char* k_HeaderXMsClientRequestId = "x-ms-client-request-id";

  // Mode "set" sets POSIX access control rights on files and directories, "modify" modifies one or more POSIX access control rights  that pre-exist on files and directories, "remove" removes one or more POSIX access control rights  that were present earlier on files and directories
  enum class PathSetAccessControlRecursiveMode
  {
    Set,
    Modify,
    Remove,
    Unknown
  };

  static std::string PathSetAccessControlRecursiveModeToString(const PathSetAccessControlRecursiveMode& pathSetAccessControlRecursiveMode)
  {
    switch (pathSetAccessControlRecursiveMode)
    {
      case PathSetAccessControlRecursiveMode::Set:
        return "set";
      case PathSetAccessControlRecursiveMode::Modify:
        return "modify";
      case PathSetAccessControlRecursiveMode::Remove:
        return "remove";
      default:
        return std::string();
    }
  }

  static PathSetAccessControlRecursiveMode PathSetAccessControlRecursiveModeFromString(const std::string& pathSetAccessControlRecursiveMode)
  {
    if (pathSetAccessControlRecursiveMode == "set")
    {
      return PathSetAccessControlRecursiveMode::Set;
    }
    if (pathSetAccessControlRecursiveMode == "modify")
    {
      return PathSetAccessControlRecursiveMode::Modify;
    }
    if (pathSetAccessControlRecursiveMode == "remove")
    {
      return PathSetAccessControlRecursiveMode::Remove;
    }
    throw std::runtime_error("Cannot convert " + pathSetAccessControlRecursiveMode + " to PathSetAccessControlRecursiveMode");
  };  // enum class PathSetAccessControlRecursiveMode

  struct AclFailedEntry
  {
    std::string Name;
    std::string Type;
    std::string ErrorMessage;

    static AclFailedEntry CreateFromJson(const nlohmann::json& node)
    {
      AclFailedEntry result;
      result.Name = node["name"].get<std::string>();
      result.Type = node["type"].get<std::string>();
      result.ErrorMessage = node["errorMessage"].get<std::string>();
      return result;
    }
  };  // struct AclFailedEntry

  struct SetAccessControlRecursiveResponse
  {
    uint64_t DirectoriesSuccessful;
    uint64_t FilesSuccessful;
    uint64_t FailureCount;
    std::vector<AclFailedEntry> FailedEntries;

    static SetAccessControlRecursiveResponse CreateFromJson(const nlohmann::json& node)
    {
      SetAccessControlRecursiveResponse result;
      result.DirectoriesSuccessful = std::stoull(node["directoriesSuccessful"].get<std::string>());
      result.FilesSuccessful = std::stoull(node["filesSuccessful"].get<std::string>());
      result.FailureCount = std::stoull(node["failureCount"].get<std::string>());
      for (const auto& element : node["failedEntries"])
      {
        result.FailedEntries.emplace_back(AclFailedEntry::CreateFromJson(element));
      }
      return result;
    }
  };  // struct SetAccessControlRecursiveResponse

  struct Path
  {
    std::string Name;
    bool IsDirectory;
    std::string LastModified;
    std::string ETag;
    uint64_t ContentLength;
    std::string Owner;
    std::string Group;
    std::string Permissions;

    static Path CreateFromJson(const nlohmann::json& node)
    {
      Path result;
      result.Name = node["name"].get<std::string>();
      result.IsDirectory = static_cast<bool>(stoi(node["isDirectory"].get<std::string>()));
      result.LastModified = node["lastModified"].get<std::string>();
      result.ETag = node["eTag"].get<std::string>();
      result.ContentLength = std::stoull(node["contentLength"].get<std::string>());
      result.Owner = node["owner"].get<std::string>();
      result.Group = node["group"].get<std::string>();
      result.Permissions = node["permissions"].get<std::string>();
      return result;
    }
  };  // struct Path

  struct PathList
  {
    std::vector<Path> Paths;

    static PathList CreateFromJson(const nlohmann::json& node)
    {
      PathList result;
      for (const auto& element : node["paths"])
      {
        result.Paths.emplace_back(Path::CreateFromJson(element));
      }
      return result;
    }
  };  // struct PathList

  struct FileSystem
  {
    std::string Name;
    std::string LastModified;
    std::string ETag;

    static FileSystem CreateFromJson(const nlohmann::json& node)
    {
      FileSystem result;
      result.Name = node["name"].get<std::string>();
      result.LastModified = node["lastModified"].get<std::string>();
      result.ETag = node["eTag"].get<std::string>();
      return result;
    }
  };  // struct FileSystem

  struct FileSystemList
  {
    std::vector<FileSystem> Filesystems;

    static FileSystemList CreateFromJson(const nlohmann::json& node)
    {
      FileSystemList result;
      for (const auto& element : node["filesystems"])
      {
        result.Filesystems.emplace_back(FileSystem::CreateFromJson(element));
      }
      return result;
    }
  };  // struct FileSystemList

  struct StorageError
  {

    // The service error response object.
    struct Error
    {
      std::string Code;  // The service error code.
      std::string Message;  // The service error message.
    };  // struct Error

    Error Error;  // The service error response object.
  };  // struct StorageError

  // Required only for Create File and Create Directory. The value must be "file" or "directory".
  enum class PathResourceType
  {
    Directory,
    File,
    Unknown
  };

  static std::string PathResourceTypeToString(const PathResourceType& pathResourceType)
  {
    switch (pathResourceType)
    {
      case PathResourceType::Directory:
        return "directory";
      case PathResourceType::File:
        return "file";
      default:
        return std::string();
    }
  }

  static PathResourceType PathResourceTypeFromString(const std::string& pathResourceType)
  {
    if (pathResourceType == "directory")
    {
      return PathResourceType::Directory;
    }
    if (pathResourceType == "file")
    {
      return PathResourceType::File;
    }
    throw std::runtime_error("Cannot convert " + pathResourceType + " to PathResourceType");
  };  // enum class PathResourceType

  // Optional. Valid only when namespace is enabled. This parameter determines the behavior of the rename operation. The value must be "legacy" or "posix", and the default value will be "posix".
  enum class PathRenameMode
  {
    Legacy,
    Posix,
    Unknown
  };

  static std::string PathRenameModeToString(const PathRenameMode& pathRenameMode)
  {
    switch (pathRenameMode)
    {
      case PathRenameMode::Legacy:
        return "legacy";
      case PathRenameMode::Posix:
        return "posix";
      default:
        return std::string();
    }
  }

  static PathRenameMode PathRenameModeFromString(const std::string& pathRenameMode)
  {
    if (pathRenameMode == "legacy")
    {
      return PathRenameMode::Legacy;
    }
    if (pathRenameMode == "posix")
    {
      return PathRenameMode::Posix;
    }
    throw std::runtime_error("Cannot convert " + pathRenameMode + " to PathRenameMode");
  };  // enum class PathRenameMode

  // The action must be "append" to upload data to be appended to a file, "flush" to flush previously uploaded data to a file, "setProperties" to set the properties of a file or directory, "setAccessControl" to set the owner, group, permissions, or access control list for a file or directory, or  "setAccessControlRecursive" to set the access control list for a directory recursively. Note that Hierarchical Namespace must be enabled for the account in order to use access control.  Also note that the Access Control List (ACL) includes permissions for the owner, owning group, and others, so the x-ms-permissions and x-ms-acl request headers are mutually exclusive.
  enum class PathUpdateAction
  {
    Append,
    Flush,
    SetProperties,
    SetAccessControl,
    SetAccessControlRecursive,
    Unknown
  };

  static std::string PathUpdateActionToString(const PathUpdateAction& pathUpdateAction)
  {
    switch (pathUpdateAction)
    {
      case PathUpdateAction::Append:
        return "append";
      case PathUpdateAction::Flush:
        return "flush";
      case PathUpdateAction::SetProperties:
        return "setProperties";
      case PathUpdateAction::SetAccessControl:
        return "setAccessControl";
      case PathUpdateAction::SetAccessControlRecursive:
        return "setAccessControlRecursive";
      default:
        return std::string();
    }
  }

  static PathUpdateAction PathUpdateActionFromString(const std::string& pathUpdateAction)
  {
    if (pathUpdateAction == "append")
    {
      return PathUpdateAction::Append;
    }
    if (pathUpdateAction == "flush")
    {
      return PathUpdateAction::Flush;
    }
    if (pathUpdateAction == "setProperties")
    {
      return PathUpdateAction::SetProperties;
    }
    if (pathUpdateAction == "setAccessControl")
    {
      return PathUpdateAction::SetAccessControl;
    }
    if (pathUpdateAction == "setAccessControlRecursive")
    {
      return PathUpdateAction::SetAccessControlRecursive;
    }
    throw std::runtime_error("Cannot convert " + pathUpdateAction + " to PathUpdateAction");
  };  // enum class PathUpdateAction

  // There are five lease actions: "acquire", "break", "change", "renew", and "release". Use "acquire" and specify the "x-ms-proposed-lease-id" and "x-ms-lease-duration" to acquire a new lease. Use "break" to break an existing lease. When a lease is broken, the lease break period is allowed to elapse, during which time no lease operation except break and release can be performed on the file. When a lease is successfully broken, the response indicates the interval in seconds until a new lease can be acquired. Use "change" and specify the current lease ID in "x-ms-lease-id" and the new lease ID in "x-ms-proposed-lease-id" to change the lease ID of an active lease. Use "renew" and specify the "x-ms-lease-id" to renew an existing lease. Use "release" and specify the "x-ms-lease-id" to release a lease.
  enum class PathLeaseAction
  {
    Acquire,
    Break,
    Change,
    Renew,
    Release,
    Unknown
  };

  static std::string PathLeaseActionToString(const PathLeaseAction& pathLeaseAction)
  {
    switch (pathLeaseAction)
    {
      case PathLeaseAction::Acquire:
        return "acquire";
      case PathLeaseAction::Break:
        return "break";
      case PathLeaseAction::Change:
        return "change";
      case PathLeaseAction::Renew:
        return "renew";
      case PathLeaseAction::Release:
        return "release";
      default:
        return std::string();
    }
  }

  static PathLeaseAction PathLeaseActionFromString(const std::string& pathLeaseAction)
  {
    if (pathLeaseAction == "acquire")
    {
      return PathLeaseAction::Acquire;
    }
    if (pathLeaseAction == "break")
    {
      return PathLeaseAction::Break;
    }
    if (pathLeaseAction == "change")
    {
      return PathLeaseAction::Change;
    }
    if (pathLeaseAction == "renew")
    {
      return PathLeaseAction::Renew;
    }
    if (pathLeaseAction == "release")
    {
      return PathLeaseAction::Release;
    }
    throw std::runtime_error("Cannot convert " + pathLeaseAction + " to PathLeaseAction");
  };  // enum class PathLeaseAction

  // Optional. If the value is "getStatus" only the system defined properties for the path are returned. If the value is "getAccessControl" the access control list is returned in the response headers (Hierarchical Namespace must be enabled for the account), otherwise the properties are returned.
  enum class PathGetPropertiesAction
  {
    GetAccessControl,
    GetStatus,
    Unknown
  };

  static std::string PathGetPropertiesActionToString(const PathGetPropertiesAction& pathGetPropertiesAction)
  {
    switch (pathGetPropertiesAction)
    {
      case PathGetPropertiesAction::GetAccessControl:
        return "getAccessControl";
      case PathGetPropertiesAction::GetStatus:
        return "getStatus";
      default:
        return std::string();
    }
  }

  static PathGetPropertiesAction PathGetPropertiesActionFromString(const std::string& pathGetPropertiesAction)
  {
    if (pathGetPropertiesAction == "getAccessControl")
    {
      return PathGetPropertiesAction::GetAccessControl;
    }
    if (pathGetPropertiesAction == "getStatus")
    {
      return PathGetPropertiesAction::GetStatus;
    }
    throw std::runtime_error("Cannot convert " + pathGetPropertiesAction + " to PathGetPropertiesAction");
  };  // enum class PathGetPropertiesAction

  struct ServiceListFileSystemsOptions
  {
    std::string Prefix = std::string();  // Filters results to filesystems within the specified prefix.
    std::string Continuation = std::string();  // Optional.  When deleting a directory, the number of paths that are deleted with each invocation is limited.  If the number of paths to be deleted exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the delete operation to continue deleting the directory.
    uint32_t MaxResults = uint32_t();  // An optional value that specifies the maximum number of items to return. If omitted or greater than 5,000, the response will include up to 5,000 items.
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request ServiceListFileSystemsCreateRequest(std::string url, const ServiceListFileSystemsOptions& serviceListFileSystemsOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
    request.AddQueryParameter(k_QueryResource, "account");
    if (!serviceListFileSystemsOptions.Prefix.empty())
    {
      request.AddQueryParameter(k_QueryPrefix, serviceListFileSystemsOptions.Prefix);
    }
    if (!serviceListFileSystemsOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, serviceListFileSystemsOptions.Continuation);
    }
    if (!std::to_string(serviceListFileSystemsOptions.MaxResults).empty())
    {
      request.AddQueryParameter(k_QueryMaxResults, std::to_string(serviceListFileSystemsOptions.MaxResults));
    }
    if (!serviceListFileSystemsOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, serviceListFileSystemsOptions.ClientRequestId);
    }
    if (!std::to_string(serviceListFileSystemsOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(serviceListFileSystemsOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, serviceListFileSystemsOptions.ApiVersionParameter);
    return request;
  }

  struct ServiceListFileSystemsResponse
  {
    FileSystemList FileSystemListObject;
    std::string Date;
    std::string RequestId;
    std::string Version;
    std::string Continuation;
    std::string ContentType;
  };

  static ServiceListFileSystemsResponse ServiceListFileSystemsParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    ServiceListFileSystemsResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // OK
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Continuation = response.GetHeaders().at(k_HeaderXMsContinuation);
      result.ContentType = response.GetHeaders().at(k_HeaderContentType);
      result.FileSystemListObject = FileSystemList::CreateFromJson(nlohmann::json::parse(response.GetBodyBuffer()));
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static ServiceListFileSystemsResponse ServiceListFileSystems(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const ServiceListFileSystemsOptions& serviceListFileSystemsOptions)
  {
    // TODO: Pipeline will be added when available.
    return ServiceListFileSystemsParseResponse(transport->Send(context, ServiceListFileSystemsCreateRequest(url, serviceListFileSystemsOptions)));
  }

  struct FileSystemCreateOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    std::string Properties = std::string();  // Optional. User-defined properties to be stored with the filesystem, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is a base64 encoded string. Note that the string may only contain ASCII characters in the ISO-8859-1 character set.  If the filesystem exists, any properties not included in the list will be removed.  All properties are removed if the header is omitted.  To merge new and existing properties, first get all existing properties and the current E-Tag, then make a conditional request with the E-Tag and include values for all properties.
  };

  static Azure::Core::Http::Request FileSystemCreateCreateRequest(std::string url, const FileSystemCreateOptions& fileSystemCreateOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
    request.AddQueryParameter(k_QueryFileSystemResource, "filesystem");
    if (!fileSystemCreateOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, fileSystemCreateOptions.ClientRequestId);
    }
    if (!std::to_string(fileSystemCreateOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(fileSystemCreateOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, fileSystemCreateOptions.ApiVersionParameter);
    if (!fileSystemCreateOptions.Properties.empty())
    {
      request.AddHeader(k_HeaderProperties, fileSystemCreateOptions.Properties);
    }
    return request;
  }

  struct FileSystemCreateResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string ClientRequestId;
    std::string Version;
    std::string NamespaceEnabled;
  };

  static FileSystemCreateResponse FileSystemCreateParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    FileSystemCreateResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
    {
      // Created
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.ClientRequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.NamespaceEnabled = response.GetHeaders().at(k_HeaderXMsNamespaceEnabled);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static FileSystemCreateResponse FileSystemCreate(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const FileSystemCreateOptions& fileSystemCreateOptions)
  {
    // TODO: Pipeline will be added when available.
    return FileSystemCreateParseResponse(transport->Send(context, FileSystemCreateCreateRequest(url, fileSystemCreateOptions)));
  }

  struct FileSystemSetPropertiesOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    std::string Properties = std::string();  // Optional. User-defined properties to be stored with the filesystem, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is a base64 encoded string. Note that the string may only contain ASCII characters in the ISO-8859-1 character set.  If the filesystem exists, any properties not included in the list will be removed.  All properties are removed if the header is omitted.  To merge new and existing properties, first get all existing properties and the current E-Tag, then make a conditional request with the E-Tag and include values for all properties.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request FileSystemSetPropertiesCreateRequest(std::string url, const FileSystemSetPropertiesOptions& fileSystemSetPropertiesOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
    request.AddQueryParameter(k_QueryFileSystemResource, "filesystem");
    if (!fileSystemSetPropertiesOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, fileSystemSetPropertiesOptions.ClientRequestId);
    }
    if (!std::to_string(fileSystemSetPropertiesOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(fileSystemSetPropertiesOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, fileSystemSetPropertiesOptions.ApiVersionParameter);
    if (!fileSystemSetPropertiesOptions.Properties.empty())
    {
      request.AddHeader(k_HeaderProperties, fileSystemSetPropertiesOptions.Properties);
    }
    if (!fileSystemSetPropertiesOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, fileSystemSetPropertiesOptions.IfModifiedSince);
    }
    if (!fileSystemSetPropertiesOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, fileSystemSetPropertiesOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct FileSystemSetPropertiesResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
  };

  static FileSystemSetPropertiesResponse FileSystemSetPropertiesParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    FileSystemSetPropertiesResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Ok
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static FileSystemSetPropertiesResponse FileSystemSetProperties(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const FileSystemSetPropertiesOptions& fileSystemSetPropertiesOptions)
  {
    // TODO: Pipeline will be added when available.
    return FileSystemSetPropertiesParseResponse(transport->Send(context, FileSystemSetPropertiesCreateRequest(url, fileSystemSetPropertiesOptions)));
  }

  struct FileSystemGetPropertiesOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request FileSystemGetPropertiesCreateRequest(std::string url, const FileSystemGetPropertiesOptions& fileSystemGetPropertiesOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Head, url);
    request.AddQueryParameter(k_QueryFileSystemResource, "filesystem");
    if (!fileSystemGetPropertiesOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, fileSystemGetPropertiesOptions.ClientRequestId);
    }
    if (!std::to_string(fileSystemGetPropertiesOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(fileSystemGetPropertiesOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, fileSystemGetPropertiesOptions.ApiVersionParameter);
    return request;
  }

  struct FileSystemGetPropertiesResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string Properties;
    std::string NamespaceEnabled;
  };

  static FileSystemGetPropertiesResponse FileSystemGetPropertiesParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    FileSystemGetPropertiesResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Ok
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Properties = response.GetHeaders().at(k_HeaderXMsProperties);
      result.NamespaceEnabled = response.GetHeaders().at(k_HeaderXMsNamespaceEnabled);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static FileSystemGetPropertiesResponse FileSystemGetProperties(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const FileSystemGetPropertiesOptions& fileSystemGetPropertiesOptions)
  {
    // TODO: Pipeline will be added when available.
    return FileSystemGetPropertiesParseResponse(transport->Send(context, FileSystemGetPropertiesCreateRequest(url, fileSystemGetPropertiesOptions)));
  }

  struct FileSystemDeleteOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request FileSystemDeleteCreateRequest(std::string url, const FileSystemDeleteOptions& fileSystemDeleteOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
    request.AddQueryParameter(k_QueryFileSystemResource, "filesystem");
    if (!fileSystemDeleteOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, fileSystemDeleteOptions.ClientRequestId);
    }
    if (!std::to_string(fileSystemDeleteOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(fileSystemDeleteOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, fileSystemDeleteOptions.ApiVersionParameter);
    if (!fileSystemDeleteOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, fileSystemDeleteOptions.IfModifiedSince);
    }
    if (!fileSystemDeleteOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, fileSystemDeleteOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct FileSystemDeleteResponse
  {
    std::string RequestId;
    std::string Version;
    std::string Date;
  };

  static FileSystemDeleteResponse FileSystemDeleteParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    FileSystemDeleteResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
    {
      // Accepted
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Date = response.GetHeaders().at(k_HeaderDate);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static FileSystemDeleteResponse FileSystemDelete(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const FileSystemDeleteOptions& fileSystemDeleteOptions)
  {
    // TODO: Pipeline will be added when available.
    return FileSystemDeleteParseResponse(transport->Send(context, FileSystemDeleteCreateRequest(url, fileSystemDeleteOptions)));
  }

  struct FileSystemListPathsOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    std::string Continuation = std::string();  // Optional.  When deleting a directory, the number of paths that are deleted with each invocation is limited.  If the number of paths to be deleted exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the delete operation to continue deleting the directory.
    std::string Directory = std::string();  // Optional.  Filters results to paths within the specified directory. An error occurs if the directory does not exist.
    bool RecursiveRequired;  // Required
    uint32_t MaxResults = uint32_t();  // An optional value that specifies the maximum number of items to return. If omitted or greater than 5,000, the response will include up to 5,000 items.
    bool Upn = bool();  // Optional. Valid only when Hierarchical Namespace is enabled for the account. If "true", the user identity values returned in the x-ms-owner, x-ms-group, and x-ms-acl response headers will be transformed from Azure Active Directory Object IDs to User Principal Names.  If "false", the values will be returned as Azure Active Directory Object IDs. The default value is false. Note that group and application Object IDs are not translated because they do not have unique friendly names.
  };

  static Azure::Core::Http::Request FileSystemListPathsCreateRequest(std::string url, const FileSystemListPathsOptions& fileSystemListPathsOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
    request.AddQueryParameter(k_QueryFileSystemResource, "filesystem");
    if (!fileSystemListPathsOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, fileSystemListPathsOptions.ClientRequestId);
    }
    if (!std::to_string(fileSystemListPathsOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(fileSystemListPathsOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, fileSystemListPathsOptions.ApiVersionParameter);
    if (!fileSystemListPathsOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, fileSystemListPathsOptions.Continuation);
    }
    if (!fileSystemListPathsOptions.Directory.empty())
    {
      request.AddQueryParameter(k_QueryDirectory, fileSystemListPathsOptions.Directory);
    }
    request.AddQueryParameter(k_QueryRecursiveRequired, std::to_string(fileSystemListPathsOptions.RecursiveRequired));
    if (!std::to_string(fileSystemListPathsOptions.MaxResults).empty())
    {
      request.AddQueryParameter(k_QueryMaxResults, std::to_string(fileSystemListPathsOptions.MaxResults));
    }
    if (!std::to_string(fileSystemListPathsOptions.Upn).empty())
    {
      request.AddQueryParameter(k_QueryUpn, std::to_string(fileSystemListPathsOptions.Upn));
    }
    return request;
  }

  struct FileSystemListPathsResponse
  {
    PathList PathListObject;
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string Continuation;
  };

  static FileSystemListPathsResponse FileSystemListPathsParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    FileSystemListPathsResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Ok
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Continuation = response.GetHeaders().at(k_HeaderXMsContinuation);
      result.PathListObject = PathList::CreateFromJson(nlohmann::json::parse(response.GetBodyBuffer()));
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static FileSystemListPathsResponse FileSystemListPaths(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const FileSystemListPathsOptions& fileSystemListPathsOptions)
  {
    // TODO: Pipeline will be added when available.
    return FileSystemListPathsParseResponse(transport->Send(context, FileSystemListPathsCreateRequest(url, fileSystemListPathsOptions)));
  }

  struct PathCreateOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    PathResourceType Resource = PathResourceType::Unknown;  // Required only for Create File and Create Directory. The value must be "file" or "directory".
    std::string Continuation = std::string();  // Optional.  When deleting a directory, the number of paths that are deleted with each invocation is limited.  If the number of paths to be deleted exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the delete operation to continue deleting the directory.
    PathRenameMode Mode = PathRenameMode::Unknown;  // Optional. Valid only when namespace is enabled. This parameter determines the behavior of the rename operation. The value must be "legacy" or "posix", and the default value will be "posix".
    std::string CacheControl = std::string();  // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentEncoding = std::string();  // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentLanguage = std::string();  // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentDisposition = std::string();  // Optional. Sets the blob's Content-Disposition header.
    std::string ContentType = std::string();  // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
    std::string RenameSource = std::string();  // An optional file or directory to be renamed.  The value must have the following format: "/{filesystem}/{path}".  If "x-ms-properties" is specified, the properties will overwrite the existing properties; otherwise, the existing properties will be preserved. This value must be a URL percent-encoded string. Note that the string may only contain ASCII characters in the ISO-8859-1 character set.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string SourceLeaseId = std::string();  // A lease ID for the source path. If specified, the source path must have an active lease and the leaase ID must match.
    std::string Properties = std::string();  // Optional. User-defined properties to be stored with the filesystem, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is a base64 encoded string. Note that the string may only contain ASCII characters in the ISO-8859-1 character set.  If the filesystem exists, any properties not included in the list will be removed.  All properties are removed if the header is omitted.  To merge new and existing properties, first get all existing properties and the current E-Tag, then make a conditional request with the E-Tag and include values for all properties.
    std::string Permissions = std::string();  // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
    std::string Umask = std::string();  // Optional and only valid if Hierarchical Namespace is enabled for the account. When creating a file or directory and the parent folder does not have a default ACL, the umask restricts the permissions of the file or directory to be created.  The resulting permission is given by p bitwise and not u, where p is the permission and u is the umask.  For example, if p is 0777 and u is 0057, then the resulting permission is 0720.  The default permission is 0777 for a directory and 0666 for a file.  The default umask is 0027.  The umask must be specified in 4-digit octal notation (e.g. 0766).
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
    std::string SourceIfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string SourceIfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string SourceIfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string SourceIfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request PathCreateCreateRequest(std::string url, const PathCreateOptions& pathCreateOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
    if (!pathCreateOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathCreateOptions.ClientRequestId);
    }
    if (!std::to_string(pathCreateOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathCreateOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathCreateOptions.ApiVersionParameter);
    if (pathCreateOptions.Resource != PathResourceType::Unknown)
    {
      request.AddQueryParameter(k_QueryPathResourceType, PathResourceTypeToString(pathCreateOptions.Resource));
    }
    if (!pathCreateOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, pathCreateOptions.Continuation);
    }
    if (pathCreateOptions.Mode != PathRenameMode::Unknown)
    {
      request.AddQueryParameter(k_QueryPathRenameMode, PathRenameModeToString(pathCreateOptions.Mode));
    }
    if (!pathCreateOptions.CacheControl.empty())
    {
      request.AddHeader(k_HeaderCacheControl, pathCreateOptions.CacheControl);
    }
    if (!pathCreateOptions.ContentEncoding.empty())
    {
      request.AddHeader(k_HeaderContentEncoding, pathCreateOptions.ContentEncoding);
    }
    if (!pathCreateOptions.ContentLanguage.empty())
    {
      request.AddHeader(k_HeaderContentLanguage, pathCreateOptions.ContentLanguage);
    }
    if (!pathCreateOptions.ContentDisposition.empty())
    {
      request.AddHeader(k_HeaderContentDisposition, pathCreateOptions.ContentDisposition);
    }
    if (!pathCreateOptions.ContentType.empty())
    {
      request.AddHeader(k_HeaderContentType, pathCreateOptions.ContentType);
    }
    if (!pathCreateOptions.RenameSource.empty())
    {
      request.AddHeader(k_HeaderRenameSource, pathCreateOptions.RenameSource);
    }
    if (!pathCreateOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathCreateOptions.LeaseIdOptional);
    }
    if (!pathCreateOptions.SourceLeaseId.empty())
    {
      request.AddHeader(k_HeaderSourceLeaseId, pathCreateOptions.SourceLeaseId);
    }
    if (!pathCreateOptions.Properties.empty())
    {
      request.AddHeader(k_HeaderProperties, pathCreateOptions.Properties);
    }
    if (!pathCreateOptions.Permissions.empty())
    {
      request.AddHeader(k_HeaderPermissions, pathCreateOptions.Permissions);
    }
    if (!pathCreateOptions.Umask.empty())
    {
      request.AddHeader(k_HeaderUmask, pathCreateOptions.Umask);
    }
    if (!pathCreateOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathCreateOptions.IfMatch);
    }
    if (!pathCreateOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathCreateOptions.IfNoneMatch);
    }
    if (!pathCreateOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathCreateOptions.IfModifiedSince);
    }
    if (!pathCreateOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathCreateOptions.IfUnmodifiedSince);
    }
    if (!pathCreateOptions.SourceIfMatch.empty())
    {
      request.AddHeader(k_HeaderSourceIfMatch, pathCreateOptions.SourceIfMatch);
    }
    if (!pathCreateOptions.SourceIfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderSourceIfNoneMatch, pathCreateOptions.SourceIfNoneMatch);
    }
    if (!pathCreateOptions.SourceIfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderSourceIfModifiedSince, pathCreateOptions.SourceIfModifiedSince);
    }
    if (!pathCreateOptions.SourceIfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderSourceIfUnmodifiedSince, pathCreateOptions.SourceIfUnmodifiedSince);
    }
    return request;
  }

  struct PathCreateResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string Continuation;
    uint64_t ContentLength;
  };

  static PathCreateResponse PathCreateParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathCreateResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
    {
      // The file or directory was created.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Continuation = response.GetHeaders().at(k_HeaderXMsContinuation);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathCreateResponse PathCreate(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathCreateOptions& pathCreateOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathCreateParseResponse(transport->Send(context, PathCreateCreateRequest(url, pathCreateOptions)));
  }

  struct PathUpdateOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    PathUpdateAction Action;  // The action must be "append" to upload data to be appended to a file, "flush" to flush previously uploaded data to a file, "setProperties" to set the properties of a file or directory, "setAccessControl" to set the owner, group, permissions, or access control list for a file or directory, or  "setAccessControlRecursive" to set the access control list for a directory recursively. Note that Hierarchical Namespace must be enabled for the account in order to use access control.  Also note that the Access Control List (ACL) includes permissions for the owner, owning group, and others, so the x-ms-permissions and x-ms-acl request headers are mutually exclusive.
    uint64_t MaxRecords;  // Optional. Valid for "SetAccessControlRecursive" operation. It specifies the maximum number of files or directories on which the acl change will be applied. If omitted or greater than 2,000, the request will process up to 2,000 items
    std::string Continuation;  // Optional. The number of paths processed with each invocation is limited. If the number of paths to be processed exceeds this limit, a continuation token is returned in the response header x-ms-continuation. When a continuation token is  returned in the response, it must be percent-encoded and specified in a subsequent invocation of setAcessControlRecursive operation.
    PathSetAccessControlRecursiveMode Mode;  // Mode "set" sets POSIX access control rights on files and directories, "modify" modifies one or more POSIX access control rights  that pre-exist on files and directories, "remove" removes one or more POSIX access control rights  that were present earlier on files and directories
    uint32_t Position = uint32_t();  // This parameter allows the caller to upload data in parallel and control the order in which it is appended to the file.  It is required when uploading data to be appended to the file and when flushing previously uploaded data to the file.  The value must be the position where the data is to be appended.  Uploaded data is not immediately flushed, or written, to the file.  To flush, the previously uploaded data must be contiguous, the position parameter must be specified and equal to the length of the file after all data has been written, and there must not be a request entity body included with the request.
    bool RetainUncommittedData = bool();  // Valid only for flush operations.  If "true", uncommitted data is retained after the flush operation completes; otherwise, the uncommitted data is deleted after the flush operation.  The default is false.  Data at offsets less than the specified position are written to the file when flush succeeds, but this optional parameter allows data after the flush position to be retained for a future flush operation.
    bool Close = bool();  // Azure Storage Events allow applications to receive notifications when files change. When Azure Storage Events are enabled, a file changed event is raised. This event has a property indicating whether this is the final change to distinguish the difference between an intermediate flush to a file stream and the final close of a file stream. The close query parameter is valid only when the action is "flush" and change notifications are enabled. If the value of close is "true" and the flush operation completes successfully, the service raises a file change notification with a property indicating that this is the final update (the file stream has been closed). If "false" a change notification is raised indicating the file has changed. The default is false. This query parameter is set to true by the Hadoop ABFS driver to indicate that the file stream has been closed."
    uint32_t ContentLength = uint32_t();  // Required for "Append Data" and "Flush Data".  Must be 0 for "Flush Data".  Must be the length of the request content in bytes for "Append Data".
    std::string ContentMD5 = std::string();  // Specify the transactional md5 for the body, to be validated by the service.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string CacheControl = std::string();  // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentType = std::string();  // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentDisposition = std::string();  // Optional. Sets the blob's Content-Disposition header.
    std::string ContentEncoding = std::string();  // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentLanguage = std::string();  // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
    std::string Properties = std::string();  // Optional. User-defined properties to be stored with the filesystem, in the format of a comma-separated list of name and value pairs "n1=v1, n2=v2, ...", where each value is a base64 encoded string. Note that the string may only contain ASCII characters in the ISO-8859-1 character set.  If the filesystem exists, any properties not included in the list will be removed.  All properties are removed if the header is omitted.  To merge new and existing properties, first get all existing properties and the current E-Tag, then make a conditional request with the E-Tag and include values for all properties.
    std::string Owner = std::string();  // Optional. The owner of the blob or directory.
    std::string Group = std::string();  // Optional. The owning group of the blob or directory.
    std::string Permissions = std::string();  // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
    std::string Acl = std::string();  // Sets POSIX access control rights on files and directories. The value is a comma-separated list of access control entries. Each access control entry (ACE) consists of a scope, a type, a user or group identifier, and permissions in the format "[scope:][type]:[id]:[permissions]".
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
    std::vector<uint8_t> Body;  // Initial data
  };

  static Azure::Core::Http::Request PathUpdateCreateRequest(std::string url, const PathUpdateOptions& pathUpdateOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url, pathUpdateOptions.Body);
    if (!pathUpdateOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathUpdateOptions.ClientRequestId);
    }
    if (!std::to_string(pathUpdateOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathUpdateOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathUpdateOptions.ApiVersionParameter);
    request.AddQueryParameter(k_QueryPathUpdateAction, PathUpdateActionToString(pathUpdateOptions.Action));
    if (!std::to_string(pathUpdateOptions.MaxRecords).empty())
    {
      request.AddQueryParameter(k_QueryMaxRecords, std::to_string(pathUpdateOptions.MaxRecords));
    }
    if (!pathUpdateOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, pathUpdateOptions.Continuation);
    }
    request.AddQueryParameter(k_QueryPathSetAccessControlRecursiveMode, PathSetAccessControlRecursiveModeToString(pathUpdateOptions.Mode));
    if (!std::to_string(pathUpdateOptions.Position).empty())
    {
      request.AddQueryParameter(k_QueryPosition, std::to_string(pathUpdateOptions.Position));
    }
    if (!std::to_string(pathUpdateOptions.RetainUncommittedData).empty())
    {
      request.AddQueryParameter(k_QueryRetainUncommittedData, std::to_string(pathUpdateOptions.RetainUncommittedData));
    }
    if (!std::to_string(pathUpdateOptions.Close).empty())
    {
      request.AddQueryParameter(k_QueryClose, std::to_string(pathUpdateOptions.Close));
    }
    if (!std::to_string(pathUpdateOptions.ContentLength).empty())
    {
      request.AddHeader(k_HeaderContentLength, std::to_string(pathUpdateOptions.ContentLength));
    }
    if (!pathUpdateOptions.ContentMD5.empty())
    {
      request.AddHeader(k_HeaderContentMD5, pathUpdateOptions.ContentMD5);
    }
    if (!pathUpdateOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathUpdateOptions.LeaseIdOptional);
    }
    if (!pathUpdateOptions.CacheControl.empty())
    {
      request.AddHeader(k_HeaderCacheControl, pathUpdateOptions.CacheControl);
    }
    if (!pathUpdateOptions.ContentType.empty())
    {
      request.AddHeader(k_HeaderContentType, pathUpdateOptions.ContentType);
    }
    if (!pathUpdateOptions.ContentDisposition.empty())
    {
      request.AddHeader(k_HeaderContentDisposition, pathUpdateOptions.ContentDisposition);
    }
    if (!pathUpdateOptions.ContentEncoding.empty())
    {
      request.AddHeader(k_HeaderContentEncoding, pathUpdateOptions.ContentEncoding);
    }
    if (!pathUpdateOptions.ContentLanguage.empty())
    {
      request.AddHeader(k_HeaderContentLanguage, pathUpdateOptions.ContentLanguage);
    }
    if (!pathUpdateOptions.Properties.empty())
    {
      request.AddHeader(k_HeaderProperties, pathUpdateOptions.Properties);
    }
    if (!pathUpdateOptions.Owner.empty())
    {
      request.AddHeader(k_HeaderOwner, pathUpdateOptions.Owner);
    }
    if (!pathUpdateOptions.Group.empty())
    {
      request.AddHeader(k_HeaderGroup, pathUpdateOptions.Group);
    }
    if (!pathUpdateOptions.Permissions.empty())
    {
      request.AddHeader(k_HeaderPermissions, pathUpdateOptions.Permissions);
    }
    if (!pathUpdateOptions.Acl.empty())
    {
      request.AddHeader(k_HeaderAcl, pathUpdateOptions.Acl);
    }
    if (!pathUpdateOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathUpdateOptions.IfMatch);
    }
    if (!pathUpdateOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathUpdateOptions.IfNoneMatch);
    }
    if (!pathUpdateOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathUpdateOptions.IfModifiedSince);
    }
    if (!pathUpdateOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathUpdateOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct PathUpdateResponse
  {
    SetAccessControlRecursiveResponse SetAccessControlRecursiveResponseObject;
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string AcceptRanges;
    std::string CacheControl;
    std::string ContentDisposition;
    std::string ContentEncoding;
    std::string ContentLanguage;
    uint64_t ContentLength;
    std::string ContentRange;
    std::string ContentType;
    std::string ContentMD5;
    std::string Properties;
    std::string XMsContinuation;
    std::string RequestId;
    std::string Version;
  };

  static PathUpdateResponse PathUpdateParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathUpdateResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // The data was flushed (written) to the file or the properties were set successfully.  Response body is optional and is valid only for "SetAccessControlRecursive"
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.AcceptRanges = response.GetHeaders().at(k_HeaderAcceptRanges);
      result.CacheControl = response.GetHeaders().at(k_HeaderCacheControl);
      result.ContentDisposition = response.GetHeaders().at(k_HeaderContentDisposition);
      result.ContentEncoding = response.GetHeaders().at(k_HeaderContentEncoding);
      result.ContentLanguage = response.GetHeaders().at(k_HeaderContentLanguage);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
      result.ContentRange = response.GetHeaders().at(k_HeaderContentRange);
      result.ContentType = response.GetHeaders().at(k_HeaderContentType);
      result.ContentMD5 = response.GetHeaders().at(k_HeaderContentMD5);
      result.Properties = response.GetHeaders().at(k_HeaderXMsProperties);
      result.XMsContinuation = response.GetHeaders().at(k_HeaderXMsContinuation);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.SetAccessControlRecursiveResponseObject = SetAccessControlRecursiveResponse::CreateFromJson(nlohmann::json::parse(response.GetBodyBuffer()));
    }
    else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
    {
      // The uploaded data was accepted.
      result.ContentMD5 = response.GetHeaders().at(k_HeaderContentMD5);
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathUpdateResponse PathUpdate(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathUpdateOptions& pathUpdateOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathUpdateParseResponse(transport->Send(context, PathUpdateCreateRequest(url, pathUpdateOptions)));
  }

  struct PathLeaseOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    PathLeaseAction XMsLeaseAction;  // There are five lease actions: "acquire", "break", "change", "renew", and "release". Use "acquire" and specify the "x-ms-proposed-lease-id" and "x-ms-lease-duration" to acquire a new lease. Use "break" to break an existing lease. When a lease is broken, the lease break period is allowed to elapse, during which time no lease operation except break and release can be performed on the file. When a lease is successfully broken, the response indicates the interval in seconds until a new lease can be acquired. Use "change" and specify the current lease ID in "x-ms-lease-id" and the new lease ID in "x-ms-proposed-lease-id" to change the lease ID of an active lease. Use "renew" and specify the "x-ms-lease-id" to renew an existing lease. Use "release" and specify the "x-ms-lease-id" to release a lease.
    uint64_t XMsLeaseDuration;  // The lease duration is required to acquire a lease, and specifies the duration of the lease in seconds.  The lease duration must be between 15 and 60 seconds or -1 for infinite lease.
    uint64_t XMsLeaseBreakPeriod;  // The lease break period duration is optional to break a lease, and  specifies the break period of the lease in seconds.  The lease break  duration must be between 0 and 60 seconds.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string ProposedLeaseIdOptional = std::string();  // Proposed lease ID, in a GUID string format. The Blob service returns 400 (Invalid request) if the proposed lease ID is not in the correct format. See Guid Constructor (String) for a list of valid GUID string formats.
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request PathLeaseCreateRequest(std::string url, const PathLeaseOptions& pathLeaseOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Post, url);
    if (!pathLeaseOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathLeaseOptions.ClientRequestId);
    }
    if (!std::to_string(pathLeaseOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathLeaseOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathLeaseOptions.ApiVersionParameter);
    request.AddHeader(k_HeaderPathLeaseAction, PathLeaseActionToString(pathLeaseOptions.XMsLeaseAction));
    if (!std::to_string(pathLeaseOptions.XMsLeaseDuration).empty())
    {
      request.AddHeader(k_HeaderXMsLeaseDuration, std::to_string(pathLeaseOptions.XMsLeaseDuration));
    }
    if (!std::to_string(pathLeaseOptions.XMsLeaseBreakPeriod).empty())
    {
      request.AddHeader(k_HeaderXMsLeaseBreakPeriod, std::to_string(pathLeaseOptions.XMsLeaseBreakPeriod));
    }
    if (!pathLeaseOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathLeaseOptions.LeaseIdOptional);
    }
    if (!pathLeaseOptions.ProposedLeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderProposedLeaseIdOptional, pathLeaseOptions.ProposedLeaseIdOptional);
    }
    if (!pathLeaseOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathLeaseOptions.IfMatch);
    }
    if (!pathLeaseOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathLeaseOptions.IfNoneMatch);
    }
    if (!pathLeaseOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathLeaseOptions.IfModifiedSince);
    }
    if (!pathLeaseOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathLeaseOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct PathLeaseResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string LeaseId;
    std::string LeaseTime;
  };

  static PathLeaseResponse PathLeaseParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathLeaseResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // The "renew", "change" or "release" action was successful.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.LeaseId = response.GetHeaders().at(k_HeaderXMsLeaseId);
    }
    else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
    {
      // A new lease has been created.  The "acquire" action was successful.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.LeaseId = response.GetHeaders().at(k_HeaderXMsLeaseId);
    }
    else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
    {
      // The "break" lease action was successful.
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.LeaseTime = response.GetHeaders().at(k_HeaderXMsLeaseTime);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathLeaseResponse PathLease(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathLeaseOptions& pathLeaseOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathLeaseParseResponse(transport->Send(context, PathLeaseCreateRequest(url, pathLeaseOptions)));
  }

  struct PathReadOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    std::string Range;  // The HTTP Range request header specifies one or more byte ranges of the resource to be retrieved.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    bool XMsRangeGetContentMd5;  // Optional. When this header is set to "true" and specified together with the Range header, the service returns the MD5 hash for the range, as long as the range is less than or equal to 4MB in size. If this header is specified without the Range header, the service returns status code 400 (Bad Request). If this header is set to true when the range exceeds 4 MB in size, the service returns status code 400 (Bad Request).
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request PathReadCreateRequest(std::string url, const PathReadOptions& pathReadOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
    if (!pathReadOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathReadOptions.ClientRequestId);
    }
    if (!std::to_string(pathReadOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathReadOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathReadOptions.ApiVersionParameter);
    if (!pathReadOptions.Range.empty())
    {
      request.AddHeader(k_HeaderRange, pathReadOptions.Range);
    }
    if (!pathReadOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathReadOptions.LeaseIdOptional);
    }
    if (!std::to_string(pathReadOptions.XMsRangeGetContentMd5).empty())
    {
      request.AddHeader(k_HeaderXMsRangeGetContentMd5, std::to_string(pathReadOptions.XMsRangeGetContentMd5));
    }
    if (!pathReadOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathReadOptions.IfMatch);
    }
    if (!pathReadOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathReadOptions.IfNoneMatch);
    }
    if (!pathReadOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathReadOptions.IfModifiedSince);
    }
    if (!pathReadOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathReadOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct PathReadResponse
  {
    std::vector<uint8_t> BodyBuffer;
    std::string AcceptRanges;
    std::string CacheControl;
    std::string ContentDisposition;
    std::string ContentEncoding;
    std::string ContentLanguage;
    uint64_t ContentLength;
    std::string ContentRange;
    std::string ContentType;
    std::string ContentMD5;
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string ResourceType;
    std::string Properties;
    std::string LeaseDuration;
    std::string LeaseState;
    std::string LeaseStatus;
    std::string XMsContentMd5;
  };

  static PathReadResponse PathReadParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathReadResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Ok
      result.AcceptRanges = response.GetHeaders().at(k_HeaderAcceptRanges);
      result.CacheControl = response.GetHeaders().at(k_HeaderCacheControl);
      result.ContentDisposition = response.GetHeaders().at(k_HeaderContentDisposition);
      result.ContentEncoding = response.GetHeaders().at(k_HeaderContentEncoding);
      result.ContentLanguage = response.GetHeaders().at(k_HeaderContentLanguage);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
      result.ContentRange = response.GetHeaders().at(k_HeaderContentRange);
      result.ContentType = response.GetHeaders().at(k_HeaderContentType);
      result.ContentMD5 = response.GetHeaders().at(k_HeaderContentMD5);
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.ResourceType = response.GetHeaders().at(k_HeaderXMsResourceType);
      result.Properties = response.GetHeaders().at(k_HeaderXMsProperties);
      result.LeaseDuration = response.GetHeaders().at(k_HeaderXMsLeaseDuration);
      result.LeaseState = response.GetHeaders().at(k_HeaderXMsLeaseState);
      result.LeaseStatus = response.GetHeaders().at(k_HeaderXMsLeaseStatus);
      result.BodyBuffer = response.GetBodyBuffer();
    }
    else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::PartialContent)
    {
      // Partial content
      result.AcceptRanges = response.GetHeaders().at(k_HeaderAcceptRanges);
      result.CacheControl = response.GetHeaders().at(k_HeaderCacheControl);
      result.ContentDisposition = response.GetHeaders().at(k_HeaderContentDisposition);
      result.ContentEncoding = response.GetHeaders().at(k_HeaderContentEncoding);
      result.ContentLanguage = response.GetHeaders().at(k_HeaderContentLanguage);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
      result.ContentRange = response.GetHeaders().at(k_HeaderContentRange);
      result.ContentType = response.GetHeaders().at(k_HeaderContentType);
      result.ContentMD5 = response.GetHeaders().at(k_HeaderContentMD5);
      result.XMsContentMd5 = response.GetHeaders().at(k_HeaderXMsContentMd5);
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.ResourceType = response.GetHeaders().at(k_HeaderXMsResourceType);
      result.Properties = response.GetHeaders().at(k_HeaderXMsProperties);
      result.LeaseDuration = response.GetHeaders().at(k_HeaderXMsLeaseDuration);
      result.LeaseState = response.GetHeaders().at(k_HeaderXMsLeaseState);
      result.LeaseStatus = response.GetHeaders().at(k_HeaderXMsLeaseStatus);
      result.BodyBuffer = response.GetBodyBuffer();
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathReadResponse PathRead(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathReadOptions& pathReadOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathReadParseResponse(transport->Send(context, PathReadCreateRequest(url, pathReadOptions)));
  }

  struct PathGetPropertiesOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    PathGetPropertiesAction Action = PathGetPropertiesAction::Unknown;  // Optional. If the value is "getStatus" only the system defined properties for the path are returned. If the value is "getAccessControl" the access control list is returned in the response headers (Hierarchical Namespace must be enabled for the account), otherwise the properties are returned.
    bool Upn = bool();  // Optional. Valid only when Hierarchical Namespace is enabled for the account. If "true", the user identity values returned in the x-ms-owner, x-ms-group, and x-ms-acl response headers will be transformed from Azure Active Directory Object IDs to User Principal Names.  If "false", the values will be returned as Azure Active Directory Object IDs. The default value is false. Note that group and application Object IDs are not translated because they do not have unique friendly names.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request PathGetPropertiesCreateRequest(std::string url, const PathGetPropertiesOptions& pathGetPropertiesOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Head, url);
    if (!pathGetPropertiesOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathGetPropertiesOptions.ClientRequestId);
    }
    if (!std::to_string(pathGetPropertiesOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathGetPropertiesOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathGetPropertiesOptions.ApiVersionParameter);
    if (pathGetPropertiesOptions.Action != PathGetPropertiesAction::Unknown)
    {
      request.AddQueryParameter(k_QueryPathGetPropertiesAction, PathGetPropertiesActionToString(pathGetPropertiesOptions.Action));
    }
    if (!std::to_string(pathGetPropertiesOptions.Upn).empty())
    {
      request.AddQueryParameter(k_QueryUpn, std::to_string(pathGetPropertiesOptions.Upn));
    }
    if (!pathGetPropertiesOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathGetPropertiesOptions.LeaseIdOptional);
    }
    if (!pathGetPropertiesOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathGetPropertiesOptions.IfMatch);
    }
    if (!pathGetPropertiesOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathGetPropertiesOptions.IfNoneMatch);
    }
    if (!pathGetPropertiesOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathGetPropertiesOptions.IfModifiedSince);
    }
    if (!pathGetPropertiesOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathGetPropertiesOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct PathGetPropertiesResponse
  {
    std::string AcceptRanges;
    std::string CacheControl;
    std::string ContentDisposition;
    std::string ContentEncoding;
    std::string ContentLanguage;
    uint64_t ContentLength;
    std::string ContentRange;
    std::string ContentType;
    std::string ContentMD5;
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string RequestId;
    std::string Version;
    std::string ResourceType;
    std::string Properties;
    std::string Owner;
    std::string Group;
    std::string Permissions;
    std::string ACL;
    std::string LeaseDuration;
    std::string LeaseState;
    std::string LeaseStatus;
  };

  static PathGetPropertiesResponse PathGetPropertiesParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathGetPropertiesResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Returns all properties for the file or directory.
      result.AcceptRanges = response.GetHeaders().at(k_HeaderAcceptRanges);
      result.CacheControl = response.GetHeaders().at(k_HeaderCacheControl);
      result.ContentDisposition = response.GetHeaders().at(k_HeaderContentDisposition);
      result.ContentEncoding = response.GetHeaders().at(k_HeaderContentEncoding);
      result.ContentLanguage = response.GetHeaders().at(k_HeaderContentLanguage);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
      result.ContentRange = response.GetHeaders().at(k_HeaderContentRange);
      result.ContentType = response.GetHeaders().at(k_HeaderContentType);
      result.ContentMD5 = response.GetHeaders().at(k_HeaderContentMD5);
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.ResourceType = response.GetHeaders().at(k_HeaderXMsResourceType);
      result.Properties = response.GetHeaders().at(k_HeaderXMsProperties);
      result.Owner = response.GetHeaders().at(k_HeaderXMsOwner);
      result.Group = response.GetHeaders().at(k_HeaderXMsGroup);
      result.Permissions = response.GetHeaders().at(k_HeaderXMsPermissions);
      result.ACL = response.GetHeaders().at(k_HeaderXMsAcl);
      result.LeaseDuration = response.GetHeaders().at(k_HeaderXMsLeaseDuration);
      result.LeaseState = response.GetHeaders().at(k_HeaderXMsLeaseState);
      result.LeaseStatus = response.GetHeaders().at(k_HeaderXMsLeaseStatus);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathGetPropertiesResponse PathGetProperties(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathGetPropertiesOptions& pathGetPropertiesOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathGetPropertiesParseResponse(transport->Send(context, PathGetPropertiesCreateRequest(url, pathGetPropertiesOptions)));
  }

  struct PathDeleteOptions
  {
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
    bool RecursiveOptional = bool();  // Required
    std::string Continuation = std::string();  // Optional.  When deleting a directory, the number of paths that are deleted with each invocation is limited.  If the number of paths to be deleted exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the delete operation to continue deleting the directory.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
  };

  static Azure::Core::Http::Request PathDeleteCreateRequest(std::string url, const PathDeleteOptions& pathDeleteOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
    if (!pathDeleteOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathDeleteOptions.ClientRequestId);
    }
    if (!std::to_string(pathDeleteOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathDeleteOptions.Timeout));
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathDeleteOptions.ApiVersionParameter);
    if (!std::to_string(pathDeleteOptions.RecursiveOptional).empty())
    {
      request.AddQueryParameter(k_QueryRecursiveOptional, std::to_string(pathDeleteOptions.RecursiveOptional));
    }
    if (!pathDeleteOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, pathDeleteOptions.Continuation);
    }
    if (!pathDeleteOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathDeleteOptions.LeaseIdOptional);
    }
    if (!pathDeleteOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathDeleteOptions.IfMatch);
    }
    if (!pathDeleteOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathDeleteOptions.IfNoneMatch);
    }
    if (!pathDeleteOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathDeleteOptions.IfModifiedSince);
    }
    if (!pathDeleteOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathDeleteOptions.IfUnmodifiedSince);
    }
    return request;
  }

  struct PathDeleteResponse
  {
    std::string Date;
    std::string RequestId;
    std::string Version;
    std::string Continuation;
  };

  static PathDeleteResponse PathDeleteParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathDeleteResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // The file was deleted.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.Continuation = response.GetHeaders().at(k_HeaderXMsContinuation);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathDeleteResponse PathDelete(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathDeleteOptions& pathDeleteOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathDeleteParseResponse(transport->Send(context, PathDeleteCreateRequest(url, pathDeleteOptions)));
  }

  struct PathSetAccessControlOptions
  {
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string Owner = std::string();  // Optional. The owner of the blob or directory.
    std::string Group = std::string();  // Optional. The owning group of the blob or directory.
    std::string Permissions = std::string();  // Optional and only valid if Hierarchical Namespace is enabled for the account. Sets POSIX access permissions for the file owner, the file owning group, and others. Each class may be granted read, write, or execute permission.  The sticky bit is also supported.  Both symbolic (rwxrw-rw-) and 4-digit octal notation (e.g. 0766) are supported.
    std::string Acl = std::string();  // Sets POSIX access control rights on files and directories. The value is a comma-separated list of access control entries. Each access control entry (ACE) consists of a scope, a type, a user or group identifier, and permissions in the format "[scope:][type]:[id]:[permissions]".
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request PathSetAccessControlCreateRequest(std::string url, const PathSetAccessControlOptions& pathSetAccessControlOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
    request.AddQueryParameter(k_QueryAction, "setAccessControl");
    if (!std::to_string(pathSetAccessControlOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathSetAccessControlOptions.Timeout));
    }
    if (!pathSetAccessControlOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathSetAccessControlOptions.LeaseIdOptional);
    }
    if (!pathSetAccessControlOptions.Owner.empty())
    {
      request.AddHeader(k_HeaderOwner, pathSetAccessControlOptions.Owner);
    }
    if (!pathSetAccessControlOptions.Group.empty())
    {
      request.AddHeader(k_HeaderGroup, pathSetAccessControlOptions.Group);
    }
    if (!pathSetAccessControlOptions.Permissions.empty())
    {
      request.AddHeader(k_HeaderPermissions, pathSetAccessControlOptions.Permissions);
    }
    if (!pathSetAccessControlOptions.Acl.empty())
    {
      request.AddHeader(k_HeaderAcl, pathSetAccessControlOptions.Acl);
    }
    if (!pathSetAccessControlOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathSetAccessControlOptions.IfMatch);
    }
    if (!pathSetAccessControlOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathSetAccessControlOptions.IfNoneMatch);
    }
    if (!pathSetAccessControlOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathSetAccessControlOptions.IfModifiedSince);
    }
    if (!pathSetAccessControlOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathSetAccessControlOptions.IfUnmodifiedSince);
    }
    if (!pathSetAccessControlOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathSetAccessControlOptions.ClientRequestId);
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathSetAccessControlOptions.ApiVersionParameter);
    return request;
  }

  struct PathSetAccessControlResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    std::string ClientRequestId;
    std::string RequestId;
    std::string Version;
  };

  static PathSetAccessControlResponse PathSetAccessControlParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathSetAccessControlResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Set directory access control response.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.ClientRequestId = response.GetHeaders().at(k_HeaderXMsClientRequestId);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathSetAccessControlResponse PathSetAccessControl(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathSetAccessControlOptions& pathSetAccessControlOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathSetAccessControlParseResponse(transport->Send(context, PathSetAccessControlCreateRequest(url, pathSetAccessControlOptions)));
  }

  struct PathSetAccessControlRecursiveOptions
  {
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    std::string Continuation = std::string();  // Optional.  When deleting a directory, the number of paths that are deleted with each invocation is limited.  If the number of paths to be deleted exceeds this limit, a continuation token is returned in this response header.  When a continuation token is returned in the response, it must be specified in a subsequent invocation of the delete operation to continue deleting the directory.
    PathSetAccessControlRecursiveMode Mode;  // Mode "set" sets POSIX access control rights on files and directories, "modify" modifies one or more POSIX access control rights  that pre-exist on files and directories, "remove" removes one or more POSIX access control rights  that were present earlier on files and directories
    uint64_t MaxRecords;  // Optional. It specifies the maximum number of files or directories on which the acl change will be applied. If omitted or greater than 2,000, the request will process up to 2,000 items
    std::string Acl = std::string();  // Sets POSIX access control rights on files and directories. The value is a comma-separated list of access control entries. Each access control entry (ACE) consists of a scope, a type, a user or group identifier, and permissions in the format "[scope:][type]:[id]:[permissions]".
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request PathSetAccessControlRecursiveCreateRequest(std::string url, const PathSetAccessControlRecursiveOptions& pathSetAccessControlRecursiveOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
    request.AddQueryParameter(k_QueryAction, "setAccessControlRecursive");
    if (!std::to_string(pathSetAccessControlRecursiveOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathSetAccessControlRecursiveOptions.Timeout));
    }
    if (!pathSetAccessControlRecursiveOptions.Continuation.empty())
    {
      request.AddQueryParameter(k_QueryContinuation, pathSetAccessControlRecursiveOptions.Continuation);
    }
    request.AddQueryParameter(k_QueryPathSetAccessControlRecursiveMode, PathSetAccessControlRecursiveModeToString(pathSetAccessControlRecursiveOptions.Mode));
    if (!std::to_string(pathSetAccessControlRecursiveOptions.MaxRecords).empty())
    {
      request.AddQueryParameter(k_QueryMaxRecords, std::to_string(pathSetAccessControlRecursiveOptions.MaxRecords));
    }
    if (!pathSetAccessControlRecursiveOptions.Acl.empty())
    {
      request.AddHeader(k_HeaderAcl, pathSetAccessControlRecursiveOptions.Acl);
    }
    if (!pathSetAccessControlRecursiveOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathSetAccessControlRecursiveOptions.ClientRequestId);
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathSetAccessControlRecursiveOptions.ApiVersionParameter);
    return request;
  }

  struct PathSetAccessControlRecursiveResponse
  {
    SetAccessControlRecursiveResponse SetAccessControlRecursiveResponseObject;
    std::string Date;
    std::string ClientRequestId;
    std::string Continuation;
    std::string RequestId;
    std::string Version;
  };

  static PathSetAccessControlRecursiveResponse PathSetAccessControlRecursiveParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathSetAccessControlRecursiveResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // Set directory access control recursive response.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ClientRequestId = response.GetHeaders().at(k_HeaderXMsClientRequestId);
      result.Continuation = response.GetHeaders().at(k_HeaderXMsContinuation);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
      result.SetAccessControlRecursiveResponseObject = SetAccessControlRecursiveResponse::CreateFromJson(nlohmann::json::parse(response.GetBodyBuffer()));
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathSetAccessControlRecursiveResponse PathSetAccessControlRecursive(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathSetAccessControlRecursiveOptions& pathSetAccessControlRecursiveOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathSetAccessControlRecursiveParseResponse(transport->Send(context, PathSetAccessControlRecursiveCreateRequest(url, pathSetAccessControlRecursiveOptions)));
  }

  struct PathFlushDataOptions
  {
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    uint32_t Position = uint32_t();  // This parameter allows the caller to upload data in parallel and control the order in which it is appended to the file.  It is required when uploading data to be appended to the file and when flushing previously uploaded data to the file.  The value must be the position where the data is to be appended.  Uploaded data is not immediately flushed, or written, to the file.  To flush, the previously uploaded data must be contiguous, the position parameter must be specified and equal to the length of the file after all data has been written, and there must not be a request entity body included with the request.
    bool RetainUncommittedData = bool();  // Valid only for flush operations.  If "true", uncommitted data is retained after the flush operation completes; otherwise, the uncommitted data is deleted after the flush operation.  The default is false.  Data at offsets less than the specified position are written to the file when flush succeeds, but this optional parameter allows data after the flush position to be retained for a future flush operation.
    bool Close = bool();  // Azure Storage Events allow applications to receive notifications when files change. When Azure Storage Events are enabled, a file changed event is raised. This event has a property indicating whether this is the final change to distinguish the difference between an intermediate flush to a file stream and the final close of a file stream. The close query parameter is valid only when the action is "flush" and change notifications are enabled. If the value of close is "true" and the flush operation completes successfully, the service raises a file change notification with a property indicating that this is the final update (the file stream has been closed). If "false" a change notification is raised indicating the file has changed. The default is false. This query parameter is set to true by the Hadoop ABFS driver to indicate that the file stream has been closed."
    uint32_t ContentLength = uint32_t();  // Required for "Append Data" and "Flush Data".  Must be 0 for "Flush Data".  Must be the length of the request content in bytes for "Append Data".
    std::string ContentMD5 = std::string();  // Specify the transactional md5 for the body, to be validated by the service.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::string CacheControl = std::string();  // Optional. Sets the blob's cache control. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentType = std::string();  // Optional. Sets the blob's content type. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentDisposition = std::string();  // Optional. Sets the blob's Content-Disposition header.
    std::string ContentEncoding = std::string();  // Optional. Sets the blob's content encoding. If specified, this property is stored with the blob and returned with a read request.
    std::string ContentLanguage = std::string();  // Optional. Set the blob's content language. If specified, this property is stored with the blob and returned with a read request.
    std::string IfMatch = std::string();  // Specify an ETag value to operate only on blobs with a matching value.
    std::string IfNoneMatch = std::string();  // Specify an ETag value to operate only on blobs without a matching value.
    std::string IfModifiedSince = std::string();  // Specify this header value to operate only on a blob if it has been modified since the specified date/time.
    std::string IfUnmodifiedSince = std::string();  // Specify this header value to operate only on a blob if it has not been modified since the specified date/time.
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request PathFlushDataCreateRequest(std::string url, const PathFlushDataOptions& pathFlushDataOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url);
    request.AddQueryParameter(k_QueryAction, "flush");
    if (!std::to_string(pathFlushDataOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathFlushDataOptions.Timeout));
    }
    if (!std::to_string(pathFlushDataOptions.Position).empty())
    {
      request.AddQueryParameter(k_QueryPosition, std::to_string(pathFlushDataOptions.Position));
    }
    if (!std::to_string(pathFlushDataOptions.RetainUncommittedData).empty())
    {
      request.AddQueryParameter(k_QueryRetainUncommittedData, std::to_string(pathFlushDataOptions.RetainUncommittedData));
    }
    if (!std::to_string(pathFlushDataOptions.Close).empty())
    {
      request.AddQueryParameter(k_QueryClose, std::to_string(pathFlushDataOptions.Close));
    }
    if (!std::to_string(pathFlushDataOptions.ContentLength).empty())
    {
      request.AddHeader(k_HeaderContentLength, std::to_string(pathFlushDataOptions.ContentLength));
    }
    if (!pathFlushDataOptions.ContentMD5.empty())
    {
      request.AddHeader(k_HeaderContentMD5, pathFlushDataOptions.ContentMD5);
    }
    if (!pathFlushDataOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathFlushDataOptions.LeaseIdOptional);
    }
    if (!pathFlushDataOptions.CacheControl.empty())
    {
      request.AddHeader(k_HeaderCacheControl, pathFlushDataOptions.CacheControl);
    }
    if (!pathFlushDataOptions.ContentType.empty())
    {
      request.AddHeader(k_HeaderContentType, pathFlushDataOptions.ContentType);
    }
    if (!pathFlushDataOptions.ContentDisposition.empty())
    {
      request.AddHeader(k_HeaderContentDisposition, pathFlushDataOptions.ContentDisposition);
    }
    if (!pathFlushDataOptions.ContentEncoding.empty())
    {
      request.AddHeader(k_HeaderContentEncoding, pathFlushDataOptions.ContentEncoding);
    }
    if (!pathFlushDataOptions.ContentLanguage.empty())
    {
      request.AddHeader(k_HeaderContentLanguage, pathFlushDataOptions.ContentLanguage);
    }
    if (!pathFlushDataOptions.IfMatch.empty())
    {
      request.AddHeader(k_HeaderIfMatch, pathFlushDataOptions.IfMatch);
    }
    if (!pathFlushDataOptions.IfNoneMatch.empty())
    {
      request.AddHeader(k_HeaderIfNoneMatch, pathFlushDataOptions.IfNoneMatch);
    }
    if (!pathFlushDataOptions.IfModifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfModifiedSince, pathFlushDataOptions.IfModifiedSince);
    }
    if (!pathFlushDataOptions.IfUnmodifiedSince.empty())
    {
      request.AddHeader(k_HeaderIfUnmodifiedSince, pathFlushDataOptions.IfUnmodifiedSince);
    }
    if (!pathFlushDataOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathFlushDataOptions.ClientRequestId);
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathFlushDataOptions.ApiVersionParameter);
    return request;
  }

  struct PathFlushDataResponse
  {
    std::string Date;
    std::string ETag;
    std::string LastModified;
    uint64_t ContentLength;
    std::string ClientRequestId;
    std::string RequestId;
    std::string Version;
  };

  static PathFlushDataResponse PathFlushDataParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathFlushDataResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
    {
      // The data was flushed (written) to the file successfully.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.ETag = response.GetHeaders().at(k_HeaderETag);
      result.LastModified = response.GetHeaders().at(k_HeaderLastModified);
      result.ContentLength = std::stoull(response.GetHeaders().at(k_HeaderContentLength));
      result.ClientRequestId = response.GetHeaders().at(k_HeaderXMsClientRequestId);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathFlushDataResponse PathFlushData(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathFlushDataOptions& pathFlushDataOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathFlushDataParseResponse(transport->Send(context, PathFlushDataCreateRequest(url, pathFlushDataOptions)));
  }

  struct PathAppendDataOptions
  {
    uint32_t Position = uint32_t();  // This parameter allows the caller to upload data in parallel and control the order in which it is appended to the file.  It is required when uploading data to be appended to the file and when flushing previously uploaded data to the file.  The value must be the position where the data is to be appended.  Uploaded data is not immediately flushed, or written, to the file.  To flush, the previously uploaded data must be contiguous, the position parameter must be specified and equal to the length of the file after all data has been written, and there must not be a request entity body included with the request.
    uint32_t Timeout = uint32_t();  // The timeout parameter is expressed in seconds. For more information, see <a href="https://docs.microsoft.com/en-us/rest/api/storageservices/fileservices/setting-timeouts-for-blob-service-operations">Setting Timeouts for Blob Service Operations.</a>
    uint32_t ContentLength = uint32_t();  // Required for "Append Data" and "Flush Data".  Must be 0 for "Flush Data".  Must be the length of the request content in bytes for "Append Data".
    std::string TransactionalContentMD5 = std::string();  // Specify the transactional md5 for the body, to be validated by the service.
    std::string LeaseIdOptional = std::string();  // If specified, the operation only succeeds if the resource's lease is active and matches this ID.
    std::vector<uint8_t> Body;  // Initial data
    std::string ClientRequestId = std::string();  // Provides a client-generated, opaque value with a 1 KB character limit that is recorded in the analytics logs when storage analytics logging is enabled.
    std::string ApiVersionParameter = k_DefaultServiceApiVersion;  // Specifies the version of the operation to use for this request.
  };

  static Azure::Core::Http::Request PathAppendDataCreateRequest(std::string url, const PathAppendDataOptions& pathAppendDataOptions)
  {
    Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Patch, url, pathAppendDataOptions.Body);
    request.AddQueryParameter(k_QueryAction, "append");
    if (!std::to_string(pathAppendDataOptions.Position).empty())
    {
      request.AddQueryParameter(k_QueryPosition, std::to_string(pathAppendDataOptions.Position));
    }
    if (!std::to_string(pathAppendDataOptions.Timeout).empty())
    {
      request.AddQueryParameter(k_QueryTimeout, std::to_string(pathAppendDataOptions.Timeout));
    }
    if (!std::to_string(pathAppendDataOptions.ContentLength).empty())
    {
      request.AddHeader(k_HeaderContentLength, std::to_string(pathAppendDataOptions.ContentLength));
    }
    if (!pathAppendDataOptions.TransactionalContentMD5.empty())
    {
      request.AddHeader(k_HeaderTransactionalContentMD5, pathAppendDataOptions.TransactionalContentMD5);
    }
    if (!pathAppendDataOptions.LeaseIdOptional.empty())
    {
      request.AddHeader(k_HeaderLeaseIdOptional, pathAppendDataOptions.LeaseIdOptional);
    }
    if (!pathAppendDataOptions.ClientRequestId.empty())
    {
      request.AddHeader(k_HeaderClientRequestId, pathAppendDataOptions.ClientRequestId);
    }
    request.AddHeader(k_HeaderApiVersionParameter, pathAppendDataOptions.ApiVersionParameter);
    return request;
  }

  struct PathAppendDataResponse
  {
    std::string Date;
    std::string RequestId;
    std::string ClientRequestId;
    std::string Version;
  };

  static PathAppendDataResponse PathAppendDataParseResponse(/*const*/ std::unique_ptr<Azure::Core::Http::Response>& responsePtr)
  {
    PathAppendDataResponse result;
    /* const */ auto& response = *responsePtr;
    if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
    {
      // Append data to file control response.
      result.Date = response.GetHeaders().at(k_HeaderDate);
      result.RequestId = response.GetHeaders().at(k_HeaderXMsRequestId);
      result.ClientRequestId = response.GetHeaders().at(k_HeaderXMsClientRequestId);
      result.Version = response.GetHeaders().at(k_HeaderXMsVersion);
    }
    else
    {
      std::cout << "Error occured:\n"
                << std::string(response.GetBodyBuffer().begin(), response.GetBodyBuffer().end()) << std::endl;
      // throw StorageError::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(response.GetBodyBuffer()));
    }
    return result;
  }

  static PathAppendDataResponse PathAppendData(std::string url, std::shared_ptr<Azure::Core::Http::HttpTransport> transport, Azure::Core::Context& context, const PathAppendDataOptions& pathAppendDataOptions)
  {
    // TODO: Pipeline will be added when available.
    return PathAppendDataParseResponse(transport->Send(context, PathAppendDataCreateRequest(url, pathAppendDataOptions)));
  }

};  // class ADLSRestClient

}  // namespace ADLS
}  // namespace Storage
}  // namespace Azure
