= deploy.gradle

//listnum[deploygradle][deploy.gradle]{
apply plugin: 'maven-publish'
apply plugin: 'org.jetbrains.dokka-android'
apply plugin: 'com.jfrog.bintray'

ext {
  libArtifactId = "helloworldlibrary"
  libGroupId = "work.kcs_labo"
  libVersion = "0.0.1"
  libName = 'HelloWorldLibrary'
  libDescription = 'Android sample library for Tech07.'
  devId = 'hide-kc'
  devName = 'KC'
  devMail = 'kcs.dev.labo@gmail.com'
  licenseName = 'MIT'
  licenseUrl = 'https://opensource.org/licenses/mit-license.php'
  siteUrl = 'https://github.com/Hide-KC/HelloWorldLibrary'
}

// This is the library version used when deploying the artifact
project.version = libVersion

dokka {
  outputFormat = 'html'
  outputDirectory = "$buildDir/javadoc"
}

task sourcesJar(type: Jar) {
  classifier = 'sources'
  from android.sourceSets.main.java.srcDirs
}

task javadocJar(type: Jar, dependsOn: dokka) {
  classifier = 'javadoc'
  from "$buildDir/javadoc"
}

def pomConfig = {
  licenses {
    license {
      name licenseName
      url licenseUrl
      distribution "repo"
    }
  }
  developers {
    developer {
      id devId
      name devName
      email devMail
    }
  }
  scm {
    url siteUrl
  }
}

def loadProperties(filename) {
  def props = new Properties()
  file(filename).withInputStream {
    props.load(it)
  }
  return props
}

project.afterEvaluate {
  publishing {
    publications {
      bintray(MavenPublication) {
        artifactId libArtifactId
        groupId libGroupId
        version libVersion

        artifact sourcesJar
        artifact javadocJar
        artifact bundleReleaseAar

        pom.withXml {
          def root = asNode()
          root.appendNode('description', libDescription)
          root.appendNode('name', libName)
          root.appendNode('url', siteUrl)
          root.children().last() + pomConfig

          def dependenciesNode = asNode().getAt('dependencies')[0] ?:
                                   asNode().appendNode('dependencies')
          configurations.implementation.allDependencies.each {
            // Ensure dependencies such as fileTree are not included.
            if (it.name != 'unspecified') {
              def dependencyNode = dependenciesNode.appendNode('dependency')
              dependencyNode.appendNode('groupId', it.group)
              dependencyNode.appendNode('artifactId', it.name)
              dependencyNode.appendNode('version', it.version)
            }
          }
        }
      }
    }
    repositories {
      maven {
        url "$buildDir/repo"
      }
    }
  }
}

bintray {
  def props = loadProperties("$gradle.gradleUserHomeDir/gradle.properties")

  user = props.bintray_user
  key = props.bintray_key
  publications = ['bintray']

  pkg {
    repo = 'maven'
    name = libName
    desc = libDescription
    publish = true
    override = true
    userOrg = devId
    licenses = [licenseName]
    vcsUrl = siteUrl + '.git'
    version {
      name = libVersion
    }
  }
}
//}